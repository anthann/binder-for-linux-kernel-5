#include <iostream>
#include "gen_clipboard_service_cb.h"

using namespace android;

enum
{
    IPCASYNCTEST = IBinder::FIRST_CALL_TRANSACTION + 2,

};

class BpClipboardService_CB : public BpInterface<IClipboardService_CB>
{
public:
    BpClipboardService_CB(const sp<IBinder> &impl)
        : BpInterface<IClipboardService_CB>(impl)
    {
    }
    int ipcAsyncTest(int32_t token, const clipboard_service::AsyncRsp& resp) {
        android::status_t ret_status = android::OK;
        Parcel data;
        ret_status = data.writeInterfaceToken(IClipboardService_CB::getInterfaceDescriptor());
        if (ret_status != android::OK) {
            return -1;
        }
        ret_status = data.writeInt32(token);
        if (ret_status != android::OK) {
            return -1;
        }
        int respSize = resp.ByteSize();
        if (respSize) {
            void *buffer = malloc(respSize);
            resp.SerializeToArray(buffer, respSize);
            ret_status = data.writeByteArray(respSize, static_cast<uint8_t *>(buffer));
            if (ret_status != android::OK) {
                return -1;
            }
            free(buffer);
        } else {
            ret_status = data.writeInt32(-1);
            if (ret_status != android::OK) {
                return -1;
            }
        }
        ret_status = remote()->transact(IPCASYNCTEST, data, NULL, IBinder::FLAG_ONEWAY);
        if (ret_status != android::OK) {
            return -1;
        }
        return 0;
    }

};

IMPLEMENT_META_INTERFACE(ClipboardService_CB, "com.tencent.cb.ClipboardService");

status_t BnClipboardService_CB::onTransact(uint32_t code, const Parcel &data, Parcel *reply, uint32_t flags)
{
    switch (code)
    {
    case IPCASYNCTEST: {
        android::status_t ret_status = android::OK;
        CHECK_INTERFACE(IClipboardService_CB, data, reply);
        int32_t token;
        ret_status = data.readInt32(&token);
        if (ret_status != android::OK) {
            return ret_status;
        }
        clipboard_service::AsyncRsp resp;
        int32_t respSize;
        ret_status = data.readInt32(&respSize);
        if (ret_status != android::OK) {
            return ret_status;
        }
        if (respSize != -1) {
            void *buffer = malloc(respSize);
            ret_status = data.read(buffer, respSize);
            if (ret_status != android::OK) {
                return ret_status;
            }
            resp.ParseFromArray(buffer, respSize);
            free(buffer);
        }
        ipcAsyncTest(token, resp);
        break;
    }

    default:
        break;
    }
    return NO_ERROR;
}
