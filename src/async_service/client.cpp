#include <iostream>
#include <unistd.h>
#include "TestCallback.h"
/*
#include "ITestInterface.h"
#include "CallbackInterfaceImpl.h"
*/

using namespace android;

int main(int argc, char **argv)
{
    /*
    sp<IServiceManager> sm = defaultServiceManager();
    sp<IBinder> binder = sm->getService(String16("service.test"));
    sp<ITestInterface> pService = interface_cast<ITestInterface>(binder);
    
    pService->InitParam(new CallbackInterfaceImpl());
    std::cout << "Add(10, 20) = " << pService->Add(10, 20) << std::endl;
    pService->CallbackTest();
    std::cout << "[client] end\n" << std::endl;
    */
    auto instance = TestCallback::instance();
    String8 msg("World");
    instance.sayHello(msg);
    int count = 12;
    while(count--) {
        sleep(1);
        if (count > 6) {
            instance.sayHello(msg);
        }
    }
    return 0;
}
