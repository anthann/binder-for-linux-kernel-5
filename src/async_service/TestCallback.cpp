#include <iostream>
#include "TestCallback.h"
#include "CallbackInterfaceImpl.h"

TestCallback::TestCallback() {
    android::ProcessState::self()->startThreadPool();
    _callback = new CallbackInterfaceImpl();
}

android::sp<ITestInterface> TestCallback::getService() {
    android::sp<ITestInterface> pService;
    android::sp<android::IServiceManager> sm = android::defaultServiceManager();
    android::sp<android::IBinder> binder;
    int timeout = 1;
    do {
        binder = sm->getService(android::String16("service.test"));
        if (binder != 0) {
            break; 
        } 
        sleep(timeout);
        timeout *= 2;
    } while(timeout < 10);
    if (binder != 0) {
        pService = android::interface_cast<ITestInterface>(binder); 
    }
    return pService;
}


void TestCallback::sayHello(android::String8 msg) {
    auto service = getService();    
    if (service == NULL) {
        std::cout << "can't get service" << std::endl; 
        return;
    }
    service->sayHello(msg, _callback);
    std::cout << "client sent: " << msg.string() << std::endl;
}
