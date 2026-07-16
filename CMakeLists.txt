cmake_minimum_required(VERSION 3.15)
project(LeetCode_CPP_Infra LANGUAGES CXX)

# 强制开启现代 C++17 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 开启严格的编译器警告
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -O2)
endif()

# 编译 #20 题可执行文件
add_executable(020_valid_parentheses src/01_stack_queue/020_valid_parentheses.cpp)
