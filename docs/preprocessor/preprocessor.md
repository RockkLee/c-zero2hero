# Preprocessor in C

## GCC stages on Linux

Before `gcc` turns your C code into a program, it goes through a few stages.

```bash
gcc main.c -o main
```

This command hides multiple steps:
1. Preprocessing
2. Compiling
3. Assembling
4. Linking

### 1. Preprocessing

The preprocessor handles lines that start with `#`.
It processes directives such as file inclusion, macro expansion, and conditional compilation.

```bash
gcc -E main.c -o main.i
```

This creates a preprocessed file such as:

- inserted header contents from `#include`
- expanded macros from `#define`
- removed code skipped by `#if`, `#ifdef`, and similar directives

### 2. Compiling

The compiler turns preprocessed C code into assembly.

```bash
gcc -S main.c -o main.s
```

### 3. Assembling

The assembler turns assembly into machine code inside an object file.

```bash
gcc -c main.c -o main.o
```

### 4. Linking

The linker combines object files and libraries into the final executable.

```bash
gcc main.o -o main
```

## What `#` means in C

Lines that begin with `#` are not normal C statements.
They are instructions for the preprocessor, which runs before the actual compiler.
These lines are called **preprocessor directives**.
They are not all macros.

Example:

```c
#include <stdio.h>
#define AGE 18

int main() {
    printf("%d\n", AGE);
}
```

Before compilation:

- `#include <stdio.h>` includes the contents of that header into the source file
- `#define AGE 18` defines a macro named `AGE`

After preprocessing, the compiler sees the expanded result, not the original source exactly as you wrote it.

## Common preprocessor directives

### `#include`

Used to include another file before compilation.

```c
#include <stdio.h>
#include "myheader.h"
```

- `<...>` usually means a system header
- `"..."` usually means a local header in your project

Conceptually, `#include` is like replacing that line with the contents of the target header file.
So yes, it acts like text inclusion during preprocessing.

### `#define`

This is simple text replacement done before compilation.
Used to define a macro.

```c
#define PI 3.14
#define SQUARE(x) ((x) * (x))
```

In `#define PI 3.14`, `PI` is the macro.
In `#define SQUARE(x) ((x) * (x))`, `SQUARE` is the macro and `x` is its parameter.

The preprocessor expands the macro before compilation.

Example:

```c
int a = SQUARE(4); // becomes ((4) * (4))
```

### `#undef`

Removes a macro definition.

```c
#define SIZE 100
#undef SIZE
```

After `#undef`, `SIZE` is no longer a macro.

### Conditional compilation

These directives decide whether some code should exist in the final preprocessed file.

```c
#define DEBUG

#ifdef DEBUG
printf("debug mode\n");
#endif
```

Common forms:

```c
#if 1
#endif

#ifdef NAME
#endif

#ifndef NAME
#endif

#if defined(NAME)
#elif defined(OTHER)
#else
#endif
```

This is often used for:

- debug-only code
- platform-specific code
- include guards in headers

### Include guards

Used to prevent a header from being included more than once.

```c
#ifndef MY_HEADER_H
#define MY_HEADER_H

int add(int a, int b);

#endif
```

### `#error`

Stops compilation with a custom message.

```c
#ifndef VERSION
#error VERSION is not defined
#endif
```

### `#pragma`

Used for compiler-specific instructions.

```c
#pragma once
```

`#pragma once` is commonly used instead of include guards, but support depends on the compiler.

## Important note

The preprocessor does not understand C like the compiler does.
It mostly does text-based substitution and file inclusion first.

That is why macros can be useful, but also dangerous if written carelessly.
