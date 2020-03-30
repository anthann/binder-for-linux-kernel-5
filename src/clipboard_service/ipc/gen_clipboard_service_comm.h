#pragma once

#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/IBinder.h>
#include <binder/Binder.h>
#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>

#include "clipboard_service.pb.h"
#include "gen_clipboard_service_cb.h"

class IClipboardService: public android::IInterface {
public:
    DECLARE_META_INTERFACE(ClipboardService);
    virtual int setText(const clipboard_service::Data& req, clipboard_service::Empty* resp) = 0;
    virtual int getText(const clipboard_service::Empty& req, clipboard_service::Data* resp) = 0;
    virtual int ipcAsyncTest(int32_t token, const clipboard_service::AsyncReq& req, const android::sp<IClipboardService_CB>& callback) = 0;

};

class BnClipboardService: public android::BnInterface<IClipboardService> {
public:
    virtual android::status_t onTransact(uint32_t code, const android::Parcel& data, android::Parcel* reply, uint32_t flags = 0);
};

