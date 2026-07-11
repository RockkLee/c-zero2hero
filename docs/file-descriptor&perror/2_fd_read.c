#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

struct database_header_t {
    unsigned short version;
    unsigned short num_employees;
    unsigned int struct_size;
};

int main(int argc, char *argv[]) {
    struct database_header_t read_head = {0};
    struct database_header_t write_head = {1, 28, sizeof(struct database_header_t)};
    struct stat db_stat = {0};

    int fd = open("./myfile.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return -1;
    }

    if (write(fd, &write_head, sizeof(write_head)) != sizeof(write_head)) {
        perror("write");
        close(fd);
        return -1;
    }

    // - lseek(fd, 0, SEEK_SET) = go to beginning
    // - lseek(fd, 0, SEEK_END) = go to end
    // - lseek(fd, 5, SEEK_CUR) = move forward 5 bytes from current position
    if (lseek(fd /*fd*/, 0 /*offset*/, SEEK_SET /*whence (from where)*/) == -1) {
        perror("lseek");
        close(fd);
        return -1;
    }

    if (read(fd /*fd*/, &read_head /*buffer*/, sizeof(read_head) /*size of the buffer*/) != sizeof(read_head)) {
        perror("read");
        close(fd);
        return -1;
    }

    printf("Version: %u\n", read_head.version);
    printf("Num of Employees: %u\n", read_head.num_employees);
    printf("File Length: %u\n", read_head.struct_size);

    // The "stat" system call to inspect file metadata.
    // This part of the code demonstrate that:
    // stat/fstat can be used to obtain the file metadata such as size, permissions, or timestamps.
    if (fstat(fd, &db_stat) < 0) {
        perror("stat");
        close(fd);
        return -1;
    }
    if (db_stat.st_size != read_head.struct_size) {
        printf("GET OUTTA HERE HACKER!\n");
        close(fd);
        return -2;
    }

    close(fd);
    return 0;
}
