#include "ICallbackInterface.h"
#include "ILoginInterface.h"
#include "CallbackInterfaceImpl.h"

class LoginClientImpl: LoginCallback {
public:
    LoginClientImpl();
    ~LoginClientImpl();    
    virtual int OnGetQrcode(const std::string& qrcode);
    virtual int OnLoginStateChange(int state, const std::string& message);

    void login();

private:
    android::sp<CallbackInterfaceImpl> _callback;
    android::sp<ILoginInterface> getService();
};
