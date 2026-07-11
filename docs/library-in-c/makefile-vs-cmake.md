# Makefile vs CMake

## Short Version

- `Makefile`: directly describes build commands
- `CMake`: describes the project, then generates the build commands

Simple mental model:

```text
Makefile = "run these commands"
CMake    = "this project has these targets and dependencies"
           -> CMake generates Makefiles or Ninja files
```

## In This Directory

In `docs/library-in-c`:

- `demo-lib` uses `CMakeLists.txt` to define:
  - a static library
  - a shared library
  - a demo executable
  - install rules
- `demo-use-a-lib` uses `CMakeLists.txt` to define:
  - an executable
  - how to find an installed library header
  - how to find an installed library file

That means you write CMake once, then CMake generates the lower-level build system.

## What a Makefile Usually Looks Like

A simple `Makefile` often contains:

- compiler variables such as `CC`, `CFLAGS`
- target names
- explicit compile commands
- explicit link commands
- explicit file dependencies

Example shape:

```make
CC = gcc
CFLAGS = -Iinc -Wall -Wextra

bin/main.o: bin/main.c inc/demo_lib.h
	$(CC) $(CFLAGS) -c bin/main.c -o bin/main.o

src/demo_lib.o: src/demo_lib.c inc/demo_lib.h
	$(CC) $(CFLAGS) -c src/demo_lib.c -o src/demo_lib.o

libdemo_lib.a: src/demo_lib.o
	ar rcs libdemo_lib.a src/demo_lib.o

demo_lib_demo: bin/main.o libdemo_lib.a
	$(CC) bin/main.o libdemo_lib.a -o demo_lib_demo
```

You are responsible for writing the actual commands.

## What CMake Usually Looks Like

Your `demo-lib/CMakeLists.txt` is higher level:

```cmake
add_library(demo_lib_static STATIC src/demo_lib.c)
add_library(demo_lib_shared SHARED src/demo_lib.c)
add_executable(demo_lib_demo bin/main.c)
target_link_libraries(demo_lib_demo PRIVATE demo_lib_static)
install(TARGETS demo_lib_static demo_lib_shared ...)
```

You describe:

- what targets exist
- what source files belong to each target
- what links to what
- what should be installed

CMake then generates the lower-level build files.

## Main Difference

With `Makefile`:

- you manage compile commands yourself
- you manage file dependency rules yourself
- you often manage platform differences yourself

With `CMake`:

- you declare targets and dependencies
- CMake generates the compile and link commands
- CMake can generate build systems for different tools

## Why CMake Feels Painful

Because there are more concepts:

- configure step
- build step
- install step
- cache variables
- target properties
- include directories
- link libraries
- `PUBLIC` / `PRIVATE` / `INTERFACE`

That is more machinery than a small hand-written `Makefile`.

## Why People Still Use CMake

For tiny projects, a `Makefile` can be easier.

For larger projects, CMake helps because it handles:

- multiple targets
- reusable libraries
- installed headers and libraries
- external dependencies
- cross-platform builds
- IDE integration

Your `demo-use-a-lib` example is exactly where CMake starts making more sense:

- one project builds and installs a library
- another project finds and links that library

Doing that by hand in raw `Makefile`s is possible, but it gets harder to maintain.

## Rule of Thumb

Use a `Makefile` when:

- the project is small
- the build is simple
- the platform is fixed
- you want direct control over commands

Use CMake when:

- the project has multiple targets
- the project exports libraries
- the project has install rules
- the project may grow
- the project may need different generators or platforms

## Practical Summary

For your current examples:

- `demo-lib`: CMake is reasonable because it builds two libraries, one executable, and install rules
- `demo-use-a-lib`: CMake is useful because it shows library discovery and linking

If both examples were only one `.c` file and one executable, a plain `Makefile` would likely be simpler.
