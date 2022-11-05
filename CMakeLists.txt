cmake_minimum_required(VERSION 3.10)

project("utility")

# 指定为C++11 版本
set(CMAKE_CXX_STANDARD 17)

# 递归查找所有cpp文件
file(GLOB_RECURSE SRCS ${CMAKE_CURRENT_SOURCE_DIR}/utility/src/*.cpp)

# 头文件查找目录
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/utility/include
)

# 生成动态库
add_library(utility SHARED ${SRCS})

# 编译测试程序
add_subdirectory(utility/test)