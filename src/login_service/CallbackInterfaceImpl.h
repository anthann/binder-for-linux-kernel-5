#pragma once

#include "ICallbackInterface.h"
class CallbackInterfaceImpl : public BnCallbackInterface
{
public:
    virtual int OnGetQrcode(const std::string& qrcode);
    virtual int OnLoginStateChange(int state, const std::string& message);
public:
    CallbackInterfaceImpl();
    virtual ~CallbackInterfaceImpl();
    void setCallback(LoginCallback *cb);
private:
    LoginCallback *callback_;
};
