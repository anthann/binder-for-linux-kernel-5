#pragma once

#include "ICallbackInterface.h"
class CallbackInterfaceImpl : public BnCallbackInterface
{
public:
    virtual void sayHello_cb(android::String8 msg);
public:
    CallbackInterfaceImpl();
    virtual ~CallbackInterfaceImpl();
};
