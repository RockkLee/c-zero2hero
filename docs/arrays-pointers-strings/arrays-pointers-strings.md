## Array
```c
#include <stdio.h>

#define MAX_IDS 5

int main() {
    // int ids[MAX_IDS] = {1, 3, 5, 7, 9};
    
    int ids[MAX_IDS];
    memset(&ids, '\0', sizeof(ids));

    ids[0] = 1;
    printf("%d\n", ids[0]);
}
```

## Pointer
```c
#include <stdio.h>

int main() {
    int x = 0x1234;
    int* px = &px;
    // %x: hexadecimal (base-16) format
    printf("%x\n", &x);
    printf("%x\n", px);
    printf("%x\n", *px);
}
```

## String
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    // A string in C is just an array of characters
    // that terminates in a null terminator, which is 0x0 or "/0".

    // Create an immutable read-only string 
    // char *arr = "abc123"; // the value of this string will be set in .rodata
    // printf("%s\n", arr);
    // arr[0] = 0x0; // get an segmentation error

    char arr = "abc123"; // create a string in Stack instead
    printf("%s\n", arr); // print: abc123
    arr[1] = 0x0;
    printf("%s\n", arr);       // print: a
    printf("%s\n", "a\0c123"); // print: a
    
    char arr2 = "abc123"
    printf("%s\n", strcmp(arr2, "abc124") ? "true" : "false"); // print: false
    // %d: int format, %ld: long format
    printf("%ld\n", strlen(arr2)); // print: 6
}
```

## Read from a string buffer
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char buff[1024];
    printf("Hey there, what's your name: ");
    // %1023s limits scanf to reading a maximum of 1,023 characters.
    // If you use plain %s, scanf will keep reading input,completely ignoring the size of your buffer.
    scanf("%1023s", buff); // the last char is the null terminator
    if (strcmp(buff, "steve")) {
        printf("damn it, steve\n");
    }
}
```
