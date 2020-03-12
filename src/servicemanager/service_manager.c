/* Copyright 2008 The Android Open Source Project
 */

#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include <selinux/android.h>
//#include <selinux/avc.h>

#include "binder.h"

#define LOG_TAG "ServiceManager"
#include <log/log.h>

struct audit_data {
    pid_t pid;
    uid_t uid;
    const char *name;
};

const char *str8(const uint16_t *x, size_t x_len)
{
    static char buf[128];
    size_t max = 127;
    char *p = buf;

    if (x_len < max) {
        max = x_len;
    }

    if (x) {
        while ((max > 0) && (*x != '\0')) {
            *p++ = *x++;
            max--;
        }
    }
    *p++ = 0;
    return buf;
}

int str16eq(const uint16_t *a, const char *b)
{
    while (*a && *b)
        if (*a++ != *b++) return 0;
    if (*a || *b)
        return 0;
    return 1;
}

static char *service_manager_context;
//static struct selabel_handle* sehandle;

static int check_mac_perms(pid_t spid, uid_t uid, const char *tctx, const char *perm, const char *name)
{
	UNUSED(spid);
	UNUSED(uid);
	UNUSED(tctx);
	UNUSED(perm);
	UNUSED(name);

	return 1;
}

static int check_mac_perms_from_getcon(pid_t spid, uid_t uid, const char *perm)
{
    return check_mac_perms(spid, uid, service_manager_context, perm, NULL);
}

static int check_mac_perms_from_lookup(pid_t spid, uid_t uid, const char *perm, const char *name)
{
    int allowed;
    char *tctx = NULL;
//
//    if (!sehandle) {
//        ALOGE("SELinux: Failed to find sehandle. Aborting service_manager.\n");
//        abort();
//    }
//
//    if (selabel_lookup(sehandle, &tctx, name, 0) != 0) {
//        ALOGE("SELinux: No match for %s in service_contexts.\n", name);
//        return 0;
//    }
//
    allowed = check_mac_perms(spid, uid, tctx, perm, name);
//    freecon(tctx);
    return allowed;
}

static int svc_can_register(const uint16_t *name, size_t name_len, pid_t spid, uid_t uid)
{
    const char *perm = "add";

//    if (multiuser_get_app_id(uid) >= AID_APP) {
//        return 0; /* Don't allow apps to register services */
//    }

    return check_mac_perms_from_lookup(spid, uid, perm, str8(name, name_len)) ? 1 : 0;
}

static int svc_can_list(pid_t spid, uid_t uid)
{
    const char *perm = "list";
    return check_mac_perms_from_getcon(spid, uid, perm) ? 1 : 0;
}

static int svc_can_find(const uint16_t *name, size_t name_len, pid_t spid, uid_t uid)
{
    const char *perm = "find";
    return check_mac_perms_from_lookup(spid, uid, perm, str8(name, name_len)) ? 1 : 0;
}

struct svcinfo
{
    struct svcinfo *next;
    uint32_t handle;
    struct binder_death death;
    int allow_isolated;
    size_t len;
    uint16_t name[0];
};

struct svcinfo *svclist = NULL;

struct svcinfo *find_svc(const uint16_t *s16, size_t len)
{
    struct svcinfo *si;

    for (si = svclist; si; si = si->next) {
        if ((len == si->len) &&
            !memcmp(s16, si->name, len * sizeof(uint16_t))) {
            return si;
        }
    }
    return NULL;
}

void svcinfo_death(struct binder_state *bs, void *ptr)
{
    struct svcinfo *si = (struct svcinfo* ) ptr;

    ALOGI("service '%s' died\n", str8(si->name, si->len));
    if (si->handle) {
        binder_release(bs, si->handle);
        si->handle = 0;
    }
}

uint16_t svcmgr_id[] = {
    'a','n','d','r','o','i','d','.','o','s','.',
    'I','S','e','r','v','i','c','e','M','a','n','a','g','e','r'
};


uint32_t do_find_service(const uint16_t *s, size_t len, uid_t uid, pid_t spid)
{
    struct svcinfo *si = find_svc(s, len);

    if (!si || !si->handle) {
        return 0;
    }

//    if (!si->allow_isolated) {
//        // If this service doesn't allow access from isolated processes,
//        // then check the uid to see if it is isolated.
//        uid_t appid = uid % AID_USER;
//        if (appid >= AID_ISOLATED_START && appid <= AID_ISOLATED_END) {
//            return 0;
//        }
//    }

    if (!svc_can_find(s, len, spid, uid)) {
        return 0;
    }

    return si->handle;
}

int do_add_service(struct binder_state *bs, const uint16_t *s, size_t len, uint32_t handle,
                   uid_t uid, int allow_isolated, pid_t spid) {
    struct svcinfo *si;

    //ALOGI("add_service('%s',%x,%s) uid=%d\n", str8(s, len), handle,
    //        allow_isolated ? "allow_isolated" : "!allow_isolated", uid);

    if (!handle || (len == 0) || (len > 127))
        return -1;

    if (!svc_can_register(s, len, spid, uid)) {
        ALOGE("add_service('%s',%x) uid=%d - PERMISSION DENIED\n",
             str8(s, len), handle, uid);
        return -1;
    }

    si = find_svc(s, len);
    if (si) {
        if (si->handle) {
            ALOGE("add_service('%s',%x) uid=%d - ALREADY REGISTERED, OVERRIDE\n",
                 str8(s, len), handle, uid);
            svcinfo_death(bs, si);
        }
        si->handle = handle;
    } else {
        si = malloc(sizeof(*si) + (len + 1) * sizeof(uint16_t));
        if (!si) {
            ALOGE("add_service('%s',%x) uid=%d - OUT OF MEMORY\n",
                 str8(s, len), handle, uid);
            return -1;
        }
        si->handle = handle;
        si->len = len;
        memcpy(si->name, s, (len + 1) * sizeof(uint16_t));
        si->name[len] = '\0';
        si->death.func = (void*) svcinfo_death;
        si->death.ptr = si;
        si->allow_isolated = allow_isolated;
        si->next = svclist;
        svclist = si;
    }

    binder_acquire(bs, handle);
    binder_link_to_death(bs, handle, &si->death);
    return 0;
}

int svcmgr_handler(struct binder_state *bs,
                   struct binder_transaction_data *txn,
                   struct binder_io *msg,
                   struct binder_io *reply)
{
    struct svcinfo *si;
    uint16_t *s;
    size_t len;
    uint32_t handle;
    int allow_isolated;

    //ALOGI("target=%p code=%d pid=%d uid=%d\n",
    //      (void*) txn->target.ptr, txn->code, txn->sender_pid, txn->sender_euid);

    if (txn->target.ptr != BINDER_SERVICE_MANAGER)
        return -1;

    if (txn->code == PING_TRANSACTION)
        return 0;

    s = bio_get_string16(msg, &len);
    if (s == NULL) {
        return -1;
    }

    if ((len != (sizeof(svcmgr_id) / 2)) ||
        memcmp(svcmgr_id, s, sizeof(svcmgr_id))) {
        fprintf(stderr,"invalid id %s\n", str8(s, len));
        return -1;
    }

    switch(txn->code) {
    case SVC_MGR_GET_SERVICE:
    case SVC_MGR_CHECK_SERVICE:
        s = bio_get_string16(msg, &len);
        if (s == NULL) {
            return -1;
        }
        handle = do_find_service(s, len, txn->sender_euid, txn->sender_pid);
        if (!handle)
            break;
        bio_put_ref(reply, handle);
        return 0;

    case SVC_MGR_ADD_SERVICE:
        s = bio_get_string16(msg, &len);
        if (s == NULL) {
            return -1;
        }
        handle = bio_get_ref(msg);
        allow_isolated = bio_get_uint32(msg) ? 1 : 0;
        if (do_add_service(bs, s, len, handle, txn->sender_euid, allow_isolated,
                           txn->sender_pid))
            return -1;
        break;

    case SVC_MGR_LIST_SERVICES: {
        uint32_t n = bio_get_uint32(msg);

        if (!svc_can_list(txn->sender_pid, txn->sender_euid)) {
            ALOGE("list_service() uid=%d - PERMISSION DENIED\n",
                    txn->sender_euid);
            return -1;
        }
        si = svclist;
        while ((n-- > 0) && si)
            si = si->next;
        if (si) {
            bio_put_string16(reply, si->name);
            return 0;
        }
        return -1;
    }
    default:
        ALOGE("unknown code %d\n", txn->code);
        return -1;
    }

    bio_put_uint32(reply, 0);
    return 0;
}

int main(int argc, char** argv)
{
    struct binder_state *bs;

    char *driver;

    if (argc > 1) {
        driver = argv[1];
    } else {
        driver = "/dev/binder";
    }

    bs = binder_open(driver, 128*1024);
    if (!bs) {
        ALOGE("failed to open binder driver %s\n", driver);
        return -1;
    }

    if (binder_become_context_manager(bs)) {
        ALOGE("cannot become context manager (%s)\n", strerror(errno));
        return -1;
    }


    binder_loop(bs, svcmgr_handler);

    return 0;
}
