#include <iostream>
#include "ICallbackInterface.h"

using namespace android;

enum
{
    ONGETQRCODE = IBinder::FIRST_CALL_TRANSACTION,
    ONLOGINSTATECHANGE = IBinder::FIRST_CALL_TRANSACTION + 1,
};

class BpCallbackInterface : public BpInterface<ICallbackInterface>
{
public:
    BpCallbackInterface(const sp<IBinder> &impl)
        : BpInterface<ICallbackInterface>(impl)
    {
    }

    virtual int OnGetQrcode(const std::string& qrcode) {
        Parcel data;
        data.writeInterfaceToken(ICallbackInterface::getInterfaceDescriptor());
        data.writeString8(String8(qrcode.c_str()));
        remote()->transact(ONGETQRCODE, data, NULL);
        return 0;
    }
    virtual int OnLoginStateChange(int state, const std::string& message) {
        Parcel data;
        data.writeInterfaceToken(ICallbackInterface::getInterfaceDescriptor());
        data.writeInt32(state);
        data.writeString8(String8(message.c_str()));
        remote()->transact(ONLOGINSTATECHANGE, data, NULL);
        return 0;
    }
};

IMPLEMENT_META_INTERFACE(CallbackInterface, "me.anthann.CallbackInterface");

status_t BnCallbackInterface::onTransact(uint32_t code, const Parcel &data, Parcel *reply, uint32_t flags)
{
    switch (code)
    {
    case ONGETQRCODE:
    {
        CHECK_INTERFACE(ICallbackInterface, data, reply);
        String8 qrcode = data.readString8();
        OnGetQrcode(qrcode.string());
        break;
    }
    case ONLOGINSTATECHANGE:
    {
        CHECK_INTERFACE(ICallbackInterface, data, reply);
        int state = data.readInt32();
        String8 message = data.readString8();
        OnLoginStateChange(state, message.string());
        break;
    }
    default:
        break;
    }
    return NO_ERROR;
}
