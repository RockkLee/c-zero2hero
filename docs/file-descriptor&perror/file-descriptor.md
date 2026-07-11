# File Descriptor

## Most I/O operations in C on POSIX systems are built on top of file descriptors

On POSIX, file descriptors are the common abstraction for many I/O targets:
```
regular files
directories
terminals
pipes
sockets
devices
stdin / stdout / stderr
```

Low-level POSIX functions directly use file descriptors:
```
read(fd, buf, size);
write(fd, buf, size);
close(fd);
```

C standard I/O functions like:
```
fread()
fwrite()
fprintf()
fgets()
```

## There are three types of file descriptors 
```c++
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    /*
     * 0 = stdin
     * 1 = stdout
     * 2 = stderr
     */
    
}
```