#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]) {
    /*
     *  [fd] --store the value as--> "file descriptor" on success, "-1" on failure
     *  0 = stdin, 1 = stdout, 2 = stderr, 3+ = files opened by open()
    */
    int fd = open(
        "./myfile.txt", //pathname
        O_RDWR | O_CREAT, // flags ("READ_WRITE flag" BinaryOr "Create flag")
        // - 6 for owner = 4 + 2 = read + write
        // - 4 for group = read only
        // - 4 for others = read only
        0644 // Unix file permission mode
    );
    if (fd == -1) {
        /*
         *  [open() Fails] ---> Returns -1 and sets global variable: errno
         *                             |
         *                             v
         *  perror("open") ----> Reads errno -> Prints: "open: <error message>"
        */
        perror("open");
        return -1;
    }

    char *mydata = "Hello World\n";
    write(fd /*fd*/, mydata /*buffer*/, strlen(mydata) /*size of the buffer*/);

    close(fd);
    return 0;
}
