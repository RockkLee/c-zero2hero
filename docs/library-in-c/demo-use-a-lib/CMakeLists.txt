cmake_minimum_required(VERSION 3.16)

project(demo_use_a_lib C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# - CACHE: store this variable in CMake’s cache, so it persists across re-runs
# - PATH: this cache entry is a filesystem path
# - "Install prefix for demo-lib": help text shown in CMake tools/UI
set(DEMO_LIB_PREFIX "/tmp/demo-lib-install" CACHE PATH "Install prefix for demo-lib")

# `find_path`: finds the directory containing a specific file
# For example:
# - Example File Structure:
#   `/opt/demo-lib/include/`
#   `├── other.h`
#   `└── helper.h`
#   `/tmp/demo-lib-install/include/`
#   `├── demo_lib.h`
#   `├── math_utils.h`
#   `└── string_utils.h`
# - Example:
#   `find_path(DEMO_LIB_INCLUDE_DIR
#      NAMES demo_lib.h
#      PATHS "/opt/demo-lib/include" "/tmp/demo-lib-install/include"
#      NO_DEFAULT_PATH
#   )`
# - Search Meaning:
#   `NAMES demo_lib.h` -> look for this header file
#   `PATHS ...` -> check these directories in order
#   first directory containing `demo_lib.h` -> returned as result
# - Result:
#   `DEMO_LIB_INCLUDE_DIR` = `/tmp/demo-lib-install/include`
find_path(DEMO_LIB_INCLUDE_DIR
    # required header = proof this is the right include dir
    NAMES demo_lib.h
    # search root = installed headers
    PATHS "${DEMO_LIB_PREFIX}/include"
    # skip system paths = example stays explicit
    NO_DEFAULT_PATH
)

# `find_library`: finds full path to a library file
# For example:
# - Example File Structure:
#   `/opt/demo-lib/lib/`
#   `├── libdemo_lib.a`
#   `└── libhelper.so`
#   `/tmp/demo-lib-install/lib/`
#   `├── libdemo_lib.so`
#   `└── libother.so`
# - Example:
#   `find_library(DEMO_LIB_LIBRARY
#      NAMES demo_lib
#      PATHS "/opt/demo-lib/lib" "/tmp/demo-lib-install/lib"
#      NO_DEFAULT_PATH
#   )`
# - Search Meaning:
#   `NAMES demo_lib` -> look for `libdemo_lib.a` or `libdemo_lib.so`
#   `PATHS ...` -> check these directories in order
#   first matching library file -> returned as result
# - Result:
#   `DEMO_LIB_LIBRARY` = `/opt/demo-lib/lib/libdemo_lib.a`
find_library(DEMO_LIB_LIBRARY
    # base name = maps to `libdemo_lib.a` or `libdemo_lib.so`
    NAMES demo_lib
    # search root = installed libraries
    PATHS "${DEMO_LIB_PREFIX}/lib"
    # skip system paths = example stays explicit
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

target_include_directories(demo_use_a_lib PRIVATE "${DEMO_LIB_INCLUDE_DIR}") # `PRIVATE` = used only to build this executable
target_link_libraries(demo_use_a_lib PRIVATE "${DEMO_LIB_LIBRARY}") # `PRIVATE` = link dependency stays on this target only
