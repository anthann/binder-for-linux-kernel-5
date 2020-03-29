cmake_minimum_required(VERSION 3.0)

project(ServiceManager)

add_executable(service_manager service_manager.c binder.c)
target_include_directories(service_manager PRIVATE ${CMAKE_SOURCE_DIR}/libs/include)
# target_link_libraries(service_manager binder)
