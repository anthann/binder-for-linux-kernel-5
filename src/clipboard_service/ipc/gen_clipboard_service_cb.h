#pragma once

#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/IBinder.h>
#include <binder/Binder.h>
#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>

#include "clipboard_service.pb.h"

//call back interface ,call by service
class IClipboardService_CB: public android::IInterface
{
public:
    DECLARE_META_INTERFACE(ClipboardService_CB);
    virtual int ipcAsyncTest(int32_t token, const clipboard_service::AsyncRsp& resp) = 0;

};

class BnClipboardService_CB: public android::BnInterface<IClipboardService_CB> {
public:
    virtual android::status_t onTransact(uint32_t code, const android::Parcel& data, android::Parcel* reply, uint32_t flags = 0);
};

