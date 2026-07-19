cmake_minimum_required(VERSION 3.15)
project(LeetCode_CPP_Infra LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) 
if(MSVC)
    add_compile_options(/W4 /WX) 
else()
    add_compile_options(-Wall -Wextra -Wpedantic -O2 -Werror)
endif()

include_directories(${CMAKE_SOURCE_DIR}/src)

set(ARRAY_POINTER_DIR ${CMAKE_SOURCE_DIR}/src/02_array_pointer)

set(LEETCODE_TARGETS
    "001_two_sum"
    "026_remove_duplicates"
    "027_remove_element"
    "088_merge_sorted_array"
)

foreach(TARGET_NAME ${LEETCODE_TARGETS})
    set(SRC_FILE "${ARRAY_POINTER_DIR}/${TARGET_NAME}.cpp")
    
    if(EXISTS ${SRC_FILE})
        add_executable(${TARGET_NAME} ${SRC_FILE})
        message(STATUS "  [Infra Build] 已成功拦截并挂载可执行靶点: ${TARGET_NAME}")
    else()
        message(AUTHOR_WARNING "  [Infra Build Warning] 未找到目标源文件: ${SRC_FILE}，跳过挂载。")
    endif()
endforeach()