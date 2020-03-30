#include <string>
#include "gen_clipboard_service_comm.h"

using namespace android;

enum {
    SETTEXT = IBinder::FIRST_CALL_TRANSACTION + 0,
    GETTEXT = IBinder::FIRST_CALL_TRANSACTION + 1,
    IPCASYNCTEST = IBinder::FIRST_CALL_TRANSACTION + 2,

};

class BpClipboardService: public BpInterface<IClipboardService> {
public:
	BpClipboardService(const sp<IBinder>& impl): BpInterface<IClipboardService>(impl) {}
    int setText(const clipboard_service::Data& req, clipboard_service::Empty* resp) {
        android::status_t ret_status = android::OK;
        android::Parcel data, reply;
        ret_status = data.writeInterfaceToken(IClipboardService::getInterfaceDescriptor());
        if (ret_status != android::OK) {
            return -1;
        }
        int reqSize = req.ByteSize();
        if (reqSize) {
            void *buffer = malloc(reqSize);
            req.SerializeToArray(buffer, reqSize);
            ret_status = data.writeByteArray(reqSize, static_cast<uint8_t *>(buffer));
            free(buffer);
            if (ret_status != android::OK) {
                return -1;
            }
        } else {
            ret_status = data.writeInt32(-1);
            if (ret_status != android::OK) {
                return -1;
            }
        }
        ret_status = remote()->transact(SETTEXT, data, &reply);
        if (ret_status != android::OK) {
            return -1;
        }
        int ret;
        ret_status = reply.readInt32(&ret);
        if (ret_status != android::OK) {
            return -1;
        }
        int respSize;
        ret_status = reply.readInt32(&respSize);
        if (respSize != -1) {
            void *buffer = malloc(respSize);
            ret_status = reply.read(buffer, respSize);
            if (ret_status != android::OK) {
                free(buffer);
                return -1;
            }
            resp->ParseFromArray(buffer, respSize);
            free(buffer);
        }
        return ret;
    }
    int getText(const clipboard_service::Empty& req, clipboard_service::Data* resp) {
        android::status_t ret_status = android::OK;
        android::Parcel data, reply;
        ret_status = data.writeInterfaceToken(IClipboardService::getInterfaceDescriptor());
        if (ret_status != android::OK) {
            return -1;
        }
        int reqSize = req.ByteSize();
        if (reqSize) {
            void *buffer = malloc(reqSize);
            req.SerializeToArray(buffer, reqSize);
            ret_status = data.writeByteArray(reqSize, static_cast<uint8_t *>(buffer));
            free(buffer);
            if (ret_status != android::OK) {
                return -1;
            }
        } else {
            ret_status = data.writeInt32(-1);
            if (ret_status != android::OK) {
                return -1;
            }
        }
        ret_status = remote()->transact(GETTEXT, data, &reply);
        if (ret_status != android::OK) {
            return -1;
        }
        int ret;
        ret_status = reply.readInt32(&ret);
        if (ret_status != android::OK) {
            return -1;
        }
        int respSize;
        ret_status = reply.readInt32(&respSize);
        if (respSize != -1) {
            void *buffer = malloc(respSize);
            ret_status = reply.read(buffer, respSize);
            if (ret_status != android::OK) {
                free(buffer);
                return -1;
            }
            resp->ParseFromArray(buffer, respSize);
            free(buffer);
        }
        return ret;
    }
    int ipcAsyncTest(int32_t token, const clipboard_service::AsyncReq& req, const android::sp<IClipboardService_CB>& callback) {
        android::status_t ret_status = android::OK;
        Parcel data;
        ret_status = data.writeInterfaceToken(IClipboardService::getInterfaceDescriptor());
        if (ret_status != android::OK) {
            return -1;
        }
        ret_status = data.writeInt32(token);
        if (ret_status != android::OK) {
            return -1;
        }
        ret_status = data.writeStrongBinder(IInterface::asBinder(callback));
        if (ret_status != android::OK) {
            return -1;
        }
        int reqSize = req.ByteSize();
        if (reqSize) {
            void *buffer = malloc(reqSize);
            req.SerializeToArray(buffer, reqSize);
            ret_status = data.writeByteArray(reqSize, static_cast<uint8_t *>(buffer));
            free(buffer);
            if (ret_status != android::OK) {
                return -1;
            }
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

IMPLEMENT_META_INTERFACE(ClipboardService, "com.tencent.weapp.os.service.clipboard_service");

status_t BnClipboardService::onTransact(uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags) {
	switch(code) {
    case SETTEXT: {
        android::status_t ret_status = android::OK;
        CHECK_INTERFACE(IClipboardService, data, reply);
        clipboard_service::Data req;
        int reqSize;
        ret_status = data.readInt32(&reqSize);
        if (ret_status != android::OK) {
            return ret_status;
        }
        if (reqSize != -1) {
            void *buffer = malloc(reqSize);
            ret_status = data.read(buffer, reqSize);
            if (ret_status != android::OK) {
                free(buffer);
                return ret_status;
            }
            req.ParseFromArray(buffer, reqSize);
            free(buffer);
        }
        clipboard_service::Empty resp;
        int ret = setText(req, &resp);
        ret_status = reply->writeInt32(ret);
        if (ret_status != android::OK) {
            return ret_status;
        }
        int respSize = resp.ByteSize();
        if (respSize) {
            void *buffer = malloc(respSize);
            resp.SerializeToArray(buffer, respSize);
            ret_status = reply->writeByteArray(respSize, static_cast<uint8_t *>(buffer));
            free(buffer);
            if (ret_status != android::OK) {
                return ret_status;
            }
        } else {
            ret_status = reply->writeInt32(-1);
            if (ret_status != android::OK) {
                return ret_status;
            }
        }
        break;
    }
    case GETTEXT: {
        android::status_t ret_status = android::OK;
        CHECK_INTERFACE(IClipboardService, data, reply);
        clipboard_service::Empty req;
        int reqSize;
        ret_status = data.readInt32(&reqSize);
        if (ret_status != android::OK) {
            return ret_status;
        }
        if (reqSize != -1) {
            void *buffer = malloc(reqSize);
            ret_status = data.read(buffer, reqSize);
            if (ret_status != android::OK) {
                free(buffer);
                return ret_status;
            }
            req.ParseFromArray(buffer, reqSize);
            free(buffer);
        }
        clipboard_service::Data resp;
        int ret = getText(req, &resp);
        ret_status = reply->writeInt32(ret);
        if (ret_status != android::OK) {
            return ret_status;
        }
        int respSize = resp.ByteSize();
        if (respSize) {
            void *buffer = malloc(respSize);
            resp.SerializeToArray(buffer, respSize);
            ret_status = reply->writeByteArray(respSize, static_cast<uint8_t *>(buffer));
            free(buffer);
            if (ret_status != android::OK) {
                return ret_status;
            }
        } else {
            ret_status = reply->writeInt32(-1);
            if (ret_status != android::OK) {
                return ret_status;
            }
        }
        break;
    }
    case IPCASYNCTEST: {
        android::status_t ret_status = android::OK;
        CHECK_INTERFACE(IClipboardService, data, reply);
        int32_t token;
        ret_status = data.readInt32(&token);
        if (ret_status != android::OK) {
            return ret_status;
        }
        android::sp<IClipboardService_CB> callback = android::interface_cast<IClipboardService_CB>(data.readStrongBinder());
        clipboard_service::AsyncReq req;
        int32_t reqSize;
        ret_status = data.readInt32(&reqSize);
        if (ret_status != android::OK) {
            return ret_status;
        }
        if (reqSize != -1) {
            void *buffer = malloc(reqSize);
            ret_status = data.read(buffer, reqSize);
            if (ret_status != android::OK) {
                free(buffer);
                return ret_status;
            }
            req.ParseFromArray(buffer, reqSize);
            free(buffer);
        }
        ipcAsyncTest(token, req, callback);
        break;
    }

	default:
		break;
	}
	return NO_ERROR;
}
