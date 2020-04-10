#include <unistd.h>
#include <iostream>
#include <thread>
#include "LoginInterfaceImpl.h"

using namespace android;

LoginInterfaceImpl::LoginInterfaceImpl() : BnLoginInterface()
{
    _callback = NULL;
}

LoginInterfaceImpl::~LoginInterfaceImpl()
{
    _callback = NULL;
}

void LoginInterfaceImpl::setCallback(const android::sp<ICallbackInterface>& callback) {
    _callback = callback;
}

void LoginInterfaceImpl::login() {
    sleep(1);
    if (_callback.get()) {
        _callback->OnGetQrcode("qrcode://ababab");
    }
    sleep(2);
    if (_callback.get()) {
        _callback->OnLoginStateChange(1, "scanned");
    }
    sleep(2);
    if (_callback.get()) {
        _callback->OnLoginStateChange(2, "logined");
    }
}
