cmake_minimum_required(VERSION 3.0)

project(AsyncTest)

add_executable(async_server 
    server.cpp 
    ITestInterface.cpp 
    ICallbackInterface.cpp 
    TestInterfaceImpl.cpp)
target_link_libraries(async_server binder)

add_executable(async_client 
    client.cpp 
    TestCallback.cpp 
    ITestInterface.cpp 
    ICallbackInterface.cpp 
    CallbackInterfaceImpl.cpp)
target_link_libraries(async_client binder)
