#include <iostream>
#include "ICallbackInterface.h"

using namespace android;

enum
{
    SAYHELLO = IBinder::FIRST_CALL_TRANSACTION,
};

class BpCallbackInterface : public BpInterface<ICallbackInterface>
{
public:
    BpCallbackInterface(const sp<IBinder> &impl)
        : BpInterface<ICallbackInterface>(impl)
    {
    }

    virtual void sayHello_cb(String8 msg) {
        Parcel data;
        data.writeInterfaceToken(ICallbackInterface::getInterfaceDescriptor());
        data.writeString8(msg);
        remote()->transact(SAYHELLO, data, NULL, IBinder::FLAG_ONEWAY);
    }
};

IMPLEMENT_META_INTERFACE(CallbackInterface, "me.anthann.CallbackInterface");

status_t BnCallbackInterface::onTransact(uint32_t code, const Parcel &data, Parcel *reply, uint32_t flags)
{
    switch (code)
    {
    case SAYHELLO:
    {
        CHECK_INTERFACE(ICallbackInterface, data, reply);
        String8 msg = data.readString8();
        sayHello_cb(msg);
        break; 
    }
    default:
        break;
    }
    return NO_ERROR;
}
