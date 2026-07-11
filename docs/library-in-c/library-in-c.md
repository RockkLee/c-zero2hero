# Static Libraries and Shared Libraries in C

A **library** is a collection of compiled object files that can be reused by multiple programs.

```text
library source files (.c)                            program source files (.c)
            |                                                   |
            v                                                   v
         compiler                                            compiler
            |                                                   |
            v                                                   v
   library object files (.o)                           program object files (.o)
        |             |                                         |
        |             +------> shared-library linker            |
        |                              |                        |
        v                              v                        |
  archiver (`ar`)             .so shared library                |
        |                              |                        |
        v                              |                        |
 .a static library                     |                        |
        |                              v                        |
        +---------------------------> linker <------------------+
                                       |
                                       v
                                 executable file
                        (for example, a program in /usr/bin)
                                       |
                                       v
                   runtime loader uses the `.so` file if needed
```

- **ELF** (Executable and Linkable Format): On Linux, many compiled binary files use **ELF**
    - `.o` files are usually ELF object files
    - `.so` files are usually ELF shared object files
    - executable files are often ELF executable files
    - `.a` files are not ELF files themselves; they are `ar` archives that contain object files

On Linux:

| Type           | Typical filename | Example          |
| -------------- | ---------------- | ---------------- |
| Static library | `lib<name>.a`    | `libmathutil.a`  |
| Shared library | `lib<name>.so`   | `libmathutil.so` |

