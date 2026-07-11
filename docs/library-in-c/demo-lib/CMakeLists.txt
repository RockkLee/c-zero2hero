cmake_minimum_required(VERSION 3.16)

project(demo_lib C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_library(demo_lib_static STATIC
    src/demo_lib.c
)

add_library(demo_lib_shared SHARED
    src/demo_lib.c
)

set_target_properties(demo_lib_static PROPERTIES OUTPUT_NAME demo_lib)
set_target_properties(demo_lib_shared PROPERTIES OUTPUT_NAME demo_lib)

target_include_directories(demo_lib_static PUBLIC inc)
target_include_directories(demo_lib_shared PUBLIC inc)

add_executable(demo_lib_demo
    bin/main.c
)

target_link_libraries(demo_lib_demo PRIVATE demo_lib_static)

install(TARGETS demo_lib_static demo_lib_shared
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(FILES inc/demo_lib.h DESTINATION include)
