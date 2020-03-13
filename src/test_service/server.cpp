#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include "IBasicService.h"

class MyBasicService: public BnBasicService {
	public:
		virtual ~MyBasicService() {}
		void sayHello() {
			std::cout << "MyBasicService::sayHello" << std::endl;	
		}

		int32_t random() {
			return rand() % 100;			
		}
};

int main() {
	sp<IServiceManager> sm = defaultServiceManager();
    if (sm.get()) {
        std::cout << "get" << std::endl; 
    }
	sm->addService(String16("service.basic"), new MyBasicService());
	ProcessState::self()->startThreadPool();
	IPCThreadState::self()->joinThreadPool();
    while (1) {
        sleep(1); 
    }
	return 0;
}
