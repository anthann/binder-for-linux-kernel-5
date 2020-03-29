#include "TestInterfaceImpl.h"

using namespace android;

int main(int argc, char **argv) {
    sp<ProcessState> proc(ProcessState::self());
    sp<IServiceManager> sm = defaultServiceManager();
    sm->addService(String16("service.test"), new TestInterfaceImpl());
    ProcessState::self()->startThreadPool(); 
    IPCThreadState::self()->joinThreadPool();
    return 0;
}
