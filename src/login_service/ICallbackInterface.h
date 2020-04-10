#pragma once

#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/IBinder.h>
#include <binder/Binder.h>
#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include <string>

class LoginCallback {
public:
    virtual int OnGetQrcode(const std::string& qrcode) = 0;
    virtual int OnLoginStateChange(int state, const std::string& message) = 0;
};

//call back interface ,call by service
class ICallbackInterface: public android::IInterface, public LoginCallback
{
public:
    DECLARE_META_INTERFACE(CallbackInterface);
};

class BnCallbackInterface: public android::BnInterface<ICallbackInterface> {
public:
    virtual android::status_t onTransact(uint32_t code, const android::Parcel& data, android::Parcel* reply, uint32_t flags = 0);
};
