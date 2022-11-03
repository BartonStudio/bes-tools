cmake_minimum_required(VERSION 3.10)

project("utility")

# 指定为C++11 版本
set(CMAKE_CXX_STANDARD 17)

# 设置变量
set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
# 头文件查找目录
include_directories(
    ${ROOT_DIR}/utility/include
)

add_library(utility SHARED ${ROOT_DIR}/utility/src/runtime_recorder.cpp)

add_executable(test test.cpp)
target_link_libraries(test utility)