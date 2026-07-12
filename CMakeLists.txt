cmake_minimum_required(VERSION 3.16)

project(c_zero2hero C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find root .c files and put them in "ROOT_SOURCES"
# - GLOB: find files matching a pattern
#     - example: "*.c" -> all .c files in that folder
# - CONFIGURE_DEPENDS: if matching files change later, CMake should re-check this glob
#     - example: you add a new .c file -> CMake notices and updates the source list on the next build/configure step
# - CMAKE_CURRENT_SOURCE_DIR : a built-in CMake variable.
#     - the source directory of the current CMakeLists.txt
file(GLOB ROOT_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
)

# Find src .c files recursively and put them in "SRC_SOURCES"
# - GLOB_RECURSE: find files matching a pattern recursively
file(GLOB_RECURSE SRC_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

# add all .c files here
add_executable(c_zero2hero
    ${ROOT_SOURCES}
    ${SRC_SOURCES}
)

# expose POSIX APIs like strdup during compilation
target_compile_definitions(c_zero2hero PRIVATE _POSIX_C_SOURCE=200809L)

# find .h files under inc/ recursively
file(GLOB_RECURSE INC_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/inc/*.h"
)

# .h files -> parent directories under inc/
set(INC_INCLUDE_DIRS "")
foreach(header ${INC_HEADERS})
    get_filename_component(header_dir "${header}" DIRECTORY)
    list(APPEND INC_INCLUDE_DIRS "${header_dir}")
endforeach()
list(REMOVE_DUPLICATES INC_INCLUDE_DIRS)

target_include_directories(c_zero2hero PRIVATE ${INC_INCLUDE_DIRS})
