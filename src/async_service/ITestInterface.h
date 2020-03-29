#pragma once

#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/IBinder.h>
#include <binder/Binder.h>
#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include "ICallbackInterface.h"

class ITestInterface : public android::IInterface
{
public:

public:
    DECLARE_META_INTERFACE(TestInterface);
    virtual void sayHello(android::String8 msg, const android::sp<ICallbackInterface>& callback) = 0;
};

class BnTestInterface : public android::BnInterface<ITestInterface>
{
public:
    virtual android::status_t onTransact(uint32_t code,
                                const android::Parcel &data,
                                android::Parcel *reply,
                                uint32_t flags = 0);
};
