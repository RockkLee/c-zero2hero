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

During configuration, CMake uses `DEMO_LIB_PREFIX` to find:

- `include/demo_lib.h`
- `lib/libdemo_lib.a` or `lib/libdemo_lib.so`

## Build steps

### 1. Build and install `demo-lib`

From the repository root:

```bash
cmake -S docs/library-in-c/demo-lib -B /tmp/demo-lib-build
cmake --build /tmp/demo-lib-build
cmake --install /tmp/demo-lib-build --prefix /tmp/demo-lib-install
```

### 2. Build `demo-use-a-lib`

```bash
cmake -S docs/library-in-c/demo-use-a-lib -B /tmp/demo-use-a-lib-build \
  -DDEMO_LIB_PREFIX=/tmp/demo-lib-install
cmake --build /tmp/demo-use-a-lib-build
```

## Why this example is useful

This shows the normal boundary between two independent projects:

- one project produces a library
- another project consumes the installed headers and compiled library files

That is closer to real library usage than placing both projects under one shared CMake build.
