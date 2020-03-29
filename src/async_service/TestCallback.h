#include "ICallbackInterface.h"
#include "ITestInterface.h"

class TestCallback {
public:
    static TestCallback& instance() {
    static TestCallback instance;
        return instance;
    }

    void sayHello(android::String8 msg);

private:
    //TestCallback(TestCallback const&) = delete;
    //void operator=(TestCallback const&) = delete;
    TestCallback();

    android::sp<ICallbackInterface> _callback;
    android::sp<ITestInterface> getService();
};
