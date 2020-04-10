#pragma once

#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/IBinder.h>
#include <binder/Binder.h>
#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include "ICallbackInterface.h"

class ILoginInterface : public android::IInterface
{
public:

public:
    DECLARE_META_INTERFACE(LoginInterface);
    virtual void setCallback(const android::sp<ICallbackInterface>& callback) = 0;
    virtual void login() = 0;
};

class BnLoginInterface : public android::BnInterface<ILoginInterface>
{
public:
    virtual android::status_t onTransact(uint32_t code,
                                const android::Parcel &data,
                                android::Parcel *reply,
                                uint32_t flags = 0);
};
