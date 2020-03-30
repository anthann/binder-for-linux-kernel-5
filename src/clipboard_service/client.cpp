#include <iostream>
#include <unistd.h>
#include "ipc/gen_clipboard_service_cli.h"

void get() {
    clipboard_service::Empty req;
    clipboard_service::Data resp;
    auto service = ClipboardServiceClient::getInstance();
    int ret = service.getText(req, &resp);
	std::cout<< "client:get: " << resp.text() << std::endl;
    std::cout << "return: " << ret << std::endl;
}

void set(std::string content) {
    clipboard_service::Data req;
    req.set_text(content);
    clipboard_service::Empty resp;
    auto service = ClipboardServiceClient::getInstance();
    int ret = service.setText(req, &resp);
    std::cout << "client:set: " << content << std::endl;
    std::cout << "return: " << ret << std::endl;
}

void callback(clipboard_service::AsyncRsp resp) {
    std::cout << "receive callback with message: " << resp.str() << std::endl;
}

void async() {
    clipboard_service::AsyncReq req;
    req.set_str("any");
    auto service = ClipboardServiceClient::getInstance();
    //service.ipcAsyncTest(req, &callback);
    service.ipcAsyncTest(req, [](clipboard_service::AsyncRsp resp){
        std::cout << "receive callback lambda with message: " << resp.str() << std::endl;
    });
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        set("default message");
        get();
    } else if (argc > 1) {
        std::string command(argv[1]);
        if (command == "get") {
            get();
        } else if (command == "set") {
            if (argc > 2) {
                std::string content(argv[2]);
                set(content);
            } else {
                set("default message");
            } 
        } else if (command == "async") {
            async();
            int count = 10;
            while (count) {
                --count;
                sleep(1); 
            }
        } else {
            std::cout << "Usage: sudo ./client (get | set [message])"  << std::endl;
        }
    }
	return 0;
}
