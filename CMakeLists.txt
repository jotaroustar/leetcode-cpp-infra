cmake_minimum_required(VERSION 3.15)
project(LeetCode_CPP_Infra LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -O2)
endif()

include_directories(${CMAKE_SOURCE_DIR}/src)

file(GLOB_RECURSE ALL_CPP_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

foreach(CPP_FILE ${ALL_CPP_FILES})
    get_filename_component(TARGET_NAME ${CPP_FILE} NAME_WE)

    add_executable(${TARGET_NAME} "${CPP_FILE}")

    message(STATUS "[Infra Build] 成功挂载独立可执行靶点: ${TARGET_NAME}")
endforeach()