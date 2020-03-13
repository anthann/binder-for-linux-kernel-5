#include <iostream>
#include "IBasicService.h"

int main() {
	sp<IServiceManager> sm = defaultServiceManager();
	sp<IBinder> binder = sm->getService(String16("service.basic"));
	sp<IBasicService> service = interface_cast<IBasicService>(binder);
	service->sayHello();
	int32_t value = service->random();
	std::cout<< "client::random recv: " << value << std::endl;
	return 0;
}
