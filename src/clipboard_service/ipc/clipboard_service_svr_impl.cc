#include <unistd.h>
#include "gen_clipboard_service_svr_impl.h"
#include "gen_clipboard_service_cb.h"
#include "../clipboard_manager.h"


int ClipboardServiceImpl::setText(const clipboard_service::Data &req,
                                  clipboard_service::Empty *resp)
{
    ClipboardManager::getInstance().setText(req.text());
    return 0;
}

int ClipboardServiceImpl::getText(const clipboard_service::Empty &req,
                                  clipboard_service::Data *resp)
{
    resp->set_text(
        ClipboardManager::getInstance().getText());
    return 0;
}

int ClipboardServiceImpl::ipcAsyncTest(int32_t token, const clipboard_service::AsyncReq& req, const android::sp<IClipboardService_CB>& callback)
{
    auto input = req.str();
    sleep(5);
    clipboard_service::AsyncRsp resp;
    resp.set_str("this is async server");
    return callback->ipcAsyncTest(token, resp);
}

