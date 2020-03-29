cmake_minimum_required(VERSION 3.0)

project(Test)

add_executable(test_server server.cpp IBasicService.cpp)
target_link_libraries(test_server binder pthread)

add_executable(test_client client.cpp IBasicService.cpp)
target_link_libraries(test_client binder pthread)
