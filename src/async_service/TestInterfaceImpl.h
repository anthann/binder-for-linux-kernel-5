#pragma once

#include "ITestInterface.h"
#include "ICallbackInterface.h"

class TestInterfaceImpl: public BnTestInterface
{
public:
    virtual void sayHello(android::String8 msg, const android::sp<ICallbackInterface>& callback);
private:
    android::sp<ICallbackInterface> _callback;

public:
    TestInterfaceImpl();
    virtual ~TestInterfaceImpl();
};
