cmake_minimum_required(VERSION 3.0)

project(ClipboardService)

add_executable(clipboard_server 
    server.cpp 
    clipboard_manager.cc
    ipc/clipboard_service.pb.cc
    ipc/gen_clipboard_service_comm.cc
    ipc/clipboard_service_svr_impl.cc
    ipc/gen_clipboard_service_cb.cc
    utils/err_def.h)
target_link_libraries(clipboard_server binder protobuf)

add_executable(clipboard_client 
    client.cpp 
    utils/err_def.h
    ipc/clipboard_service.pb.cc
    ipc/gen_clipboard_service_comm.cc
    ipc/gen_clipboard_service_cb.cc
    ipc/gen_clipboard_service_cb_impl.cc
    ipc/gen_clipboard_service_cli.cc)
target_link_libraries(clipboard_client binder protobuf)
