#pragma once

#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/IBinder.h>
#include <binder/Binder.h>
#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>

//call back interface ,call by service
class ICallbackInterface: public android::IInterface
{
public:
    DECLARE_META_INTERFACE(CallbackInterface);
    virtual void sayHello_cb(android::String8 msg) = 0;
};

class BnCallbackInterface: public android::BnInterface<ICallbackInterface> {
public:
    virtual android::status_t onTransact(uint32_t code, const android::Parcel& data, android::Parcel* reply, uint32_t flags = 0);
};
