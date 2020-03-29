#include <unistd.h>
#include <iostream>
#include "TestInterfaceImpl.h"

using namespace android;

TestInterfaceImpl::TestInterfaceImpl() : BnTestInterface()
{
}

TestInterfaceImpl::~TestInterfaceImpl()
{
}

void TestInterfaceImpl::sayHello(String8 msg, const sp<ICallbackInterface>& callback) {
    std::cout << "server receive: " << msg << std::endl;
    sleep(5);      
    //auto cb = callback.promote();
    String8 rt("Reveived: ");
    rt.append(msg);
    if (callback.get()) {
        std::cout << "server reply: " << rt << std::endl;
        callback->sayHello_cb(rt); 
    } else {
        std::cout << "server wake up but callback is gone" << std::endl; 
    }
}
