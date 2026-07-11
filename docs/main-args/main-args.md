# main args

```c
// assume the filename of this program is `main.c`
// `gcc main.c -o main`
// `./main hello` -> print: hello
// `./main hello world` -> print: hello world

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
    // argc:
    //   argument count
    //   the number of command-line arguments passed to this program
    //   including the program name itself
    //
    // **argv: a pointer that points to a `char*`
    //   argument vector
    //   an array of strings containing the command-line arguments
    //   argv[0] -> *(argv + 0) -> is the program name
    //   argv[1] -> *(argv + 1) -> is the first argument after the program name
    //   argv[2] -> *(argv + 2) -> is the second argument, and so on
    
    if (argc == 2) {
        printf("%s\n", argv[1]);
    }
    if (argc == 3) {
        printf("%s\n", argv[1]);
        printf("%s\n", argv[2]);
    }
}
```