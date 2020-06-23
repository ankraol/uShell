 #include "header.h"

void mx_printchar_fd(char c, int fd) {
    write(fd, &c, 1);
}
