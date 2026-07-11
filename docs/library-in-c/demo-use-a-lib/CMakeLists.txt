cmake_minimum_required(VERSION 3.16)

project(demo_use_a_lib C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(DEMO_LIB_PREFIX "" CACHE PATH "Install prefix for demo-lib")

find_path(DEMO_LIB_INCLUDE_DIR
    NAMES demo_lib.h
    PATHS "${DEMO_LIB_PREFIX}/include"
    NO_DEFAULT_PATH
)

find_library(DEMO_LIB_LIBRARY
    NAMES demo_lib
    PATHS "${DEMO_LIB_PREFIX}/lib"
    NO_DEFAULT_PATH
)

if(NOT DEMO_LIB_INCLUDE_DIR OR NOT DEMO_LIB_LIBRARY)
    message(FATAL_ERROR
        "demo-lib not found. Build and install demo-lib first, then configure with "
        "-DDEMO_LIB_PREFIX=/path/to/demo-lib-install"
    )
endif()

add_executable(demo_use_a_lib
    bin/main.c
)

target_include_directories(demo_use_a_lib PRIVATE "${DEMO_LIB_INCLUDE_DIR}")
target_link_libraries(demo_use_a_lib PRIVATE "${DEMO_LIB_LIBRARY}")
