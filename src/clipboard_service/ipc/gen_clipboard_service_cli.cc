#include <iostream>
#include "gen_clipboard_service_cli.h"


static int32_t token = 0;

ClipboardServiceClient::ClipboardServiceClient() {
    android::ProcessState::self()->startThreadPool();
    _callback = new ClipboardService_CB_Impl();

}

android::sp<IClipboardService> ClipboardServiceClient::getService() {
    android::sp<IClipboardService> pService;
    android::sp<android::IServiceManager> sm = android::defaultServiceManager();
    android::sp<android::IBinder> binder;
    int timeout = 1;
    do {
        binder = sm->getService(android::String16("service.ClipboardService"));
        if (binder != 0) {
            break; 
        } 
        sleep(timeout);
        timeout *= 2;
    } while(timeout < 10);
    if (binder != 0) {
        pService = android::interface_cast<IClipboardService>(binder); 
    }
    return pService;
}

int ClipboardServiceClient::setText(const clipboard_service::Data& req, clipboard_service::Empty* resp) {
    auto service = getService();
    if (service == NULL) {
        std::cerr << "can't get service" << std::endl; 
        return -1;
    }
    return service->setText(req, resp);
}

int ClipboardServiceClient::setText(const std::string& text,  clipboard_service::Empty* resp) {
    clipboard_service::Data req;
req.set_text(text);
    return setText(req, resp);
}
int ClipboardServiceClient::getText(const clipboard_service::Empty& req, clipboard_service::Data* resp) {
    auto service = getService();
    if (service == NULL) {
        std::cerr << "can't get service" << std::endl; 
        return -1;
    }
    return service->getText(req, resp);
}

int ClipboardServiceClient::getText( clipboard_service::Data* resp) {
    clipboard_service::Empty req;
    return getText(req, resp);
}
void ClipboardServiceClient::ipcAsyncTest(const clipboard_service::AsyncReq& req, void (*callback)(clipboard_service::AsyncRsp)) {
    auto service = getService();
    if (service == NULL) {
        std::cerr << "can't get service" << std::endl; 
        return;
    }
    int32_t _t = token++;
    AsyncRsp_cbt cbt = {
        _t,
        callback,
    };
    _callback->addipcAsyncTestCallback(cbt);
    service->ipcAsyncTest(_t, req, _callback);
}

void ClipboardServiceClient::ipcAsyncTest(const std::string& str,  void (*callback)(clipboard_service::AsyncRsp)) {
    clipboard_service::AsyncReq req;
req.set_str(str);
    ipcAsyncTest(req, callback);
}

