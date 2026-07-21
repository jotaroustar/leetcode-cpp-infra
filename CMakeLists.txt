cmake_minimum_required(VERSION 3.15)
project(LeetCode_CPP_Infra LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -O2 -Werror)
endif()

include_directories(${CMAKE_SOURCE_DIR}/src)

# ==============================================================================
# 核心自动化构建逻辑：自动递归搜索 src 下所有 .cpp 文件并独立挂载可执行文件
# ==============================================================================

# 1. 自动遍历 src 目录及所有子目录下（如 01_stack_queue, 02_array_pointer 等）的 cpp 文件
file(GLOB_RECURSE ALL_CPP_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

foreach(CPP_FILE ${ALL_CPP_FILES})
    # 2. 从文件路径中提取无后缀的文件名（例如从 ".../011_container_with_most_water.cpp" 提取出 "011_container_with_most_water"）
    get_filename_component(TARGET_NAME ${CPP_FILE} NAME_WE)

    # 3. 每一个 cpp 文件单独生成一个独立的 exe 目标，彻底解决 main() 重定义冲突！
    add_executable(${TARGET_NAME} ${CPP_FILE})

    message(STATUS "[Infra Build] 成功挂载独立可执行靶点: ${TARGET_NAME}")
endforeach()