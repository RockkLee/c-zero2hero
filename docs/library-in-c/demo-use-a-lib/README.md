# demo-use-a-lib

`demo-use-a-lib` is a separate standalone C project that demonstrates how another program can use `demo-lib`.

## Layout

```text
demo-use-a-lib/
├── bin/
│   └── main.c
├── CMakeLists.txt
└── README.md
```

- `bin/main.c`: executable source that includes `demo_lib.h` and calls `add`
- `CMakeLists.txt`: standalone build script that locates an installed `demo-lib`

## How it works

This project does not build `demo-lib` from source.

Instead, it expects `demo-lib` to already be installed somewhere, with:

- headers under `include/`
- libraries under `lib/`

During configuration, CMake uses:

- `DEMO_LIB_PREFIX`: install root for `demo-lib`
- `find_path(...)`: finds the directory containing `demo_lib.h`
- `find_library(...)`: finds `libdemo_lib.a` or `libdemo_lib.so`

By default, `DEMO_LIB_PREFIX` is:

```text
/tmp/demo-lib-install
```

## Build steps

### 1. Build and install `demo-lib`

From the repository root:

```bash
# configure `demo-lib`
# - `-S docs/library-in-c/demo-lib`: source dir
# - `-B /tmp/demo-lib-build`: gen CMake build system (plan) for the later compile step
cmake -S docs/library-in-c/demo-lib -B /tmp/demo-lib-build

# invoke the build system (plan) to compile the project
# The generated build system (/tmp/demo-lib-build/...) --> gcc/clang/MSVC --> .o object files --> library files + executable files
cmake --build /tmp/demo-lib-build

# `--install /tmp/demo-lib-build`: install from this build dir
# `--prefix /tmp/demo-lib-install`: place installed files under this dir
# result:
# - `/tmp/demo-lib-install/include/demo_lib.h`
# - `/tmp/demo-lib-install/lib/libdemo_lib.a`
# - `/tmp/demo-lib-install/lib/libdemo_lib.so`
cmake --install /tmp/demo-lib-build --prefix /tmp/demo-lib-install
```

### 2. Build `demo-use-a-lib`

```bash
cmake -S docs/library-in-c/demo-use-a-lib -B build
cmake --build build
```

```bash
cmake -S docs/library-in-c/demo-use-a-lib -B build \
  -DDEMO_LIB_PREFIX=/tmp/demo-lib-install # override the variable in the CMake file
cmake --build build
```

## Run

After building:

```bash
./build/demo_use_a_lib
```

- runs the compiled demo executable directly

## Why this example is useful

This shows the normal boundary between two independent projects:

- one project produces a library
- another project consumes the installed headers and compiled library files

That is closer to real library usage than placing both projects under one shared CMake build.
