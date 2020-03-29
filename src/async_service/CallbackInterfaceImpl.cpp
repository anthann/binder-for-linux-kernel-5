#include <iostream>
#include "CallbackInterfaceImpl.h"

CallbackInterfaceImpl::CallbackInterfaceImpl()
{
}

CallbackInterfaceImpl::~CallbackInterfaceImpl()
{
}

void CallbackInterfaceImpl::sayHello_cb(android::String8 msg) {
    std::cout << "CallbackInterfaceImpl::sayHello_cb msg=" << msg.string() << std::endl;
}
