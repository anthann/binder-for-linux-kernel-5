#include <iostream>
#include <unistd.h>
#include "LoginClientImpl.h"

using namespace android;

int main(int argc, char **argv)
{
    LoginClientImpl *instance = new LoginClientImpl();
    instance->login();
    int count = 10;
    while(count--) {
        sleep(1);
        std::cout << "." << std::endl;
    }
    delete instance;
    return 0;
}
