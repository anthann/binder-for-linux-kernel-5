#pragma once

#include "ILoginInterface.h"
#include "ICallbackInterface.h"

class LoginInterfaceImpl: public BnLoginInterface
{
public:
    virtual void setCallback(const android::sp<ICallbackInterface>& callback);
    virtual void login();
private:
    android::sp<ICallbackInterface> _callback;

public:
    LoginInterfaceImpl();
    virtual ~LoginInterfaceImpl();
};
