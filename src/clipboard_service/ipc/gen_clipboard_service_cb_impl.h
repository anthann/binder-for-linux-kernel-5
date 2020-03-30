#pragma once

#include <vector>
//#include <mutex>
#include "gen_clipboard_service_cb.h"


struct AsyncRsp_cbt {
    int token;
    void (*cb)(clipboard_service::AsyncRsp);
};


class ClipboardService_CB_Impl : public BnClipboardService_CB
{
public:
    virtual int ipcAsyncTest(int32_t token, const clipboard_service::AsyncRsp& resp);
    void addipcAsyncTestCallback(AsyncRsp_cbt cb);
public:
    ClipboardService_CB_Impl();
    virtual ~ClipboardService_CB_Impl();
private:
    std::vector<AsyncRsp_cbt> ipcAsyncTest_cbs;
 //   std::mutex mtx;
};
 
