#include <iostream>
#include "LoginClientImpl.h"


LoginClientImpl::LoginClientImpl() {
    android::ProcessState::self()->startThreadPool();
    _callback = new CallbackInterfaceImpl();
    _callback->setCallback(this);
}

LoginClientImpl::~LoginClientImpl() {
}

int LoginClientImpl::OnGetQrcode(const std::string& qrcode) {
    std::cout << "cli OnGetQrcode: " << qrcode << std::endl;
}

int LoginClientImpl::OnLoginStateChange(int state, const std::string& message) {
    std::cout << "cli OnLoginStateChange: " << state << " message: " << message << std::endl;
}

void LoginClientImpl::login() {
    auto service = getService();    
    if (service == NULL) {
        std::cout << "can't get service" << std::endl; 
        return;
    }
    service->setCallback(_callback);
    service->login();
}

android::sp<ILoginInterface> LoginClientImpl::getService() {
    android::sp<ILoginInterface> pService;
    android::sp<android::IServiceManager> sm = android::defaultServiceManager();
    android::sp<android::IBinder> binder;
    int timeout = 1;
    do {
        binder = sm->getService(android::String16("service.login"));
        if (binder != 0) {
            break; 
        } 
        sleep(timeout);
        timeout *= 2;
    } while(timeout < 10);
    if (binder != 0) {
        pService = android::interface_cast<ILoginInterface>(binder); 
    }
    return pService;
}