# demo-lib

`demo-lib` is a tiny standalone C project that builds a reusable library and a small demo program.

## Layout

```text
demo-lib/
├── bin/
│   └── main.c
├── inc/
│   └── demo_lib.h
├── src/
│   └── demo_lib.c
├── CMakeLists.txt
└── README.md
```

- `inc/`: public headers that other programs include
- `src/`: library implementation
- `bin/`: example executable that uses the library
- `CMakeLists.txt`: standalone build script

## What it builds

This project creates:

- `libdemo_lib.a`: static library
- `libdemo_lib.so`: shared library
- `demo_lib_demo`: example executable

The library currently exports one function:

```c
int add(int left, int right);
```

## Build

From the repository root:

```bash
# CMake configure: source -> docs/library-in-c/demo-lib, build files -> /tmp/demo-lib-build
cmake -S docs/library-in-c/demo-lib -B /tmp/demo-lib-build
# CMake build: generated build files -> compiled targets
cmake --build /tmp/demo-lib-build
```

## Install

To make the library easy for another project to consume:

```bash
# CMake install: build output -> /tmp/demo-lib-install
cmake --install /tmp/demo-lib-build --prefix /tmp/demo-lib-install
```

That install prefix will contain:

```text
/tmp/demo-lib-install/
├── include/
│   └── demo_lib.h
└── lib/
    ├── libdemo_lib.a
    └── libdemo_lib.so
```

## Why both static and shared libraries exist

- Static library (`.a`): copied into the executable at link time
- Shared library (`.so`): loaded at runtime

This project builds both to demonstrate the common library outputs on Linux.
