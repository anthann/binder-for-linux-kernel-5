#include <string>
#include "IBasicService.h"

enum {
	HELLO = IBinder::FIRST_CALL_TRANSACTION,
	RANDOM = IBinder::FIRST_CALL_TRANSACTION + 1,
};

class BpBasicService: public BpInterface<IBasicService> {
	public:
		BpBasicService(const sp<IBinder>& impl): BpInterface<IBasicService>(impl) {}
		void sayHello() {
			printf("BpBasicService::sayHello\n");
			Parcel data, reply;
			data.writeInterfaceToken(IBasicService::getInterfaceDescriptor());
			remote()->transact(HELLO, data, &reply);
			printf("BpBasicService::sayHello: got response from BnBasicService\n");	
		}

		int32_t random() {
			printf("BpBasicService::random\n");
			Parcel data, reply;
			data.writeInterfaceToken(IBasicService::getInterfaceDescriptor());
			remote()->transact(RANDOM, data, &reply);
			int32_t value = reply.readInt32();
			printf("BpBasicService::random: got random number from BnBasicService: %d\n", value);	
			return value;
		}
};

IMPLEMENT_META_INTERFACE(BasicService, "me.anthann.basicservice");

status_t BnBasicService::onTransact(uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags) {
	switch(code) {
	case HELLO: {
		printf("BnBasicService:: got the client hello\n");
		CHECK_INTERFACE(IBasicService, data, reply);
		sayHello();
		break;
	}	
	case RANDOM: {
		printf("BnBasicService:: got the client random\n");
		CHECK_INTERFACE(IBasicService, data, reply);
		int32_t value = random();
		reply->writeInt32(value);
		break;
		
	}
	default:
		break;
	}
	return NO_ERROR;
}
