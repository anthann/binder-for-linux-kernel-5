#include "gen_clipboard_service_comm.h"

class ClipboardServiceImpl: public BnClipboardService {
public:
    virtual ~ClipboardServiceImpl() {}   
    int pureMem(int len, const char *buf);
    virtual int setText(const clipboard_service::Data& req, clipboard_service::Empty* resp);
    virtual int getText(const clipboard_service::Empty& req, clipboard_service::Data* resp);
    virtual int ipcAsyncTest(int32_t token, const clipboard_service::AsyncReq& req, const android::sp<IClipboardService_CB>& callback);

};

