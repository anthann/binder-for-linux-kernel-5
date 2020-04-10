#include "ILoginInterface.h"
#include <iostream>

using namespace android;

enum
{
    SETCALLBACK = android::IBinder::FIRST_CALL_TRANSACTION,
    LOGIN = android::IBinder::FIRST_CALL_TRANSACTION + 1,
};

class BpLoginInterface : public BpInterface<ILoginInterface>
{
public:
    BpLoginInterface(const sp<IBinder> &impl)
        : BpInterface<ILoginInterface>(impl)
    {
    }

    virtual void setCallback(const android::sp<ICallbackInterface>& callback) {
        Parcel data;
        data.writeInterfaceToken(ILoginInterface::getInterfaceDescriptor());
        data.writeStrongBinder(IInterface::asBinder(callback));
        remote()->transact(SETCALLBACK, data, NULL);
    }

    virtual void login() {
        Parcel data;
        data.writeInterfaceToken(ILoginInterface::getInterfaceDescriptor());
        remote()->transact(LOGIN, data, NULL);
    }
};

IMPLEMENT_META_INTERFACE(LoginInterface, "me.anthann.ILoginService");

status_t BnLoginInterface::onTransact(
    uint32_t code, const Parcel &data, Parcel *reply, uint32_t flags)
{
    switch (code)
    {
    case SETCALLBACK:
    {
        CHECK_INTERFACE(ILoginInterface, data, reply);
        sp<ICallbackInterface> callback = interface_cast<ICallbackInterface>(data.readStrongBinder());
        setCallback(callback);
        break;
    }
    case LOGIN:
        CHECK_INTERFACE(ILoginInterface, data, reply);
        login();
        break;
    default:
        break;
    }
    return NO_ERROR;
}
