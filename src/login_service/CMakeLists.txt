cmake_minimum_required(VERSION 3.0)

project(LoginServer)

add_executable(login_server 
    server.cpp 
    ILoginInterface.cpp 
    ICallbackInterface.cpp 
    LoginInterfaceImpl.cpp)
target_link_libraries(login_server binder)

add_executable(login_client 
    client.cpp 
    LoginClientImpl.cpp 
    ILoginInterface.cpp 
    ICallbackInterface.cpp 
    CallbackInterfaceImpl.cpp)
target_link_libraries(login_client binder)
