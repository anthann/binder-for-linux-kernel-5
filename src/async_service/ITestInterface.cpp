#include "ITestInterface.h"

using namespace android;

enum
{
    SAYHELLO = android::IBinder::FIRST_CALL_TRANSACTION,
};

class BpTestInterface : public BpInterface<ITestInterface>
{
public:
    BpTestInterface(const sp<IBinder> &impl)
        : BpInterface<ITestInterface>(impl)
    {
    }

    virtual void sayHello(String8 msg, const sp<ICallbackInterface>& callback) {
        Parcel data, reply;
        data.writeInterfaceToken(ITestInterface::getInterfaceDescriptor());
        //auto s = callback.promote();
        //if (s == NULL) {
        //    return; 
        //}
        data.writeStrongBinder(IInterface::asBinder(callback));
        data.writeString8(msg);
        remote()->transact(SAYHELLO, data, &reply, IBinder::FLAG_ONEWAY);
    }
};

IMPLEMENT_META_INTERFACE(TestInterface, "me.anthann.ITestInterface");

status_t BnTestInterface::onTransact(
    uint32_t code, const Parcel &data, Parcel *reply, uint32_t flags)
{
    switch (code)
    {
    case SAYHELLO:
    {
        CHECK_INTERFACE(ITestInterface, data, reply);
        sp<ICallbackInterface> callback = interface_cast<ICallbackInterface>(data.readStrongBinder());
        String8 a = data.readString8();
        sayHello(a, callback);
        break;
    }
    default:
        break;
    }
    return NO_ERROR;
}
