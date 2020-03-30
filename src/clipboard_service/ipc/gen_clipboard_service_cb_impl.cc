#include <iostream>
#include <mutex>
#include "gen_clipboard_service_cb_impl.h"

static std::mutex mtx;


ClipboardService_CB_Impl::ClipboardService_CB_Impl()
{
}

ClipboardService_CB_Impl::~ClipboardService_CB_Impl()
{
}

int ClipboardService_CB_Impl::ipcAsyncTest(int32_t token, const clipboard_service::AsyncRsp& resp) {
    for(auto it = ipcAsyncTest_cbs.begin(); it != ipcAsyncTest_cbs.end(); ++it) {
        if (it->token == token) {
            it->cb(resp);
            mtx.lock();
            ipcAsyncTest_cbs.erase(it);
            mtx.unlock();
            break;
        }
    }
}


void ClipboardService_CB_Impl::addipcAsyncTestCallback(AsyncRsp_cbt cb) {
    mtx.lock();
    ipcAsyncTest_cbs.push_back(cb);
    mtx.unlock();
}


