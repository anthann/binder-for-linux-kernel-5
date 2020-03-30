#include "gen_clipboard_service_comm.h"
#include "gen_clipboard_service_cb_impl.h"


class ClipboardServiceClient {
public:
    static ClipboardServiceClient& getInstance() {
        static ClipboardServiceClient instance;
        return instance;
    }

    int setText(const clipboard_service::Data& req, clipboard_service::Empty* resp);
    int setText(const std::string& text,  clipboard_service::Empty* resp);
    int getText(const clipboard_service::Empty& req, clipboard_service::Data* resp);
    int getText( clipboard_service::Data* resp);
    void ipcAsyncTest(const clipboard_service::AsyncReq& req, void (*callback)(clipboard_service::AsyncRsp));
    void ipcAsyncTest(const std::string& str,  void (*callback)(clipboard_service::AsyncRsp));


private:
    ClipboardServiceClient();
    android::sp<ClipboardService_CB_Impl> _callback;
    android::sp<IClipboardService> getService();
};
