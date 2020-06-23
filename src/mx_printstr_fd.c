 #include "header.h"


void mx_printstr_fd(const char *s, int fd) {
	int size = mx_strlen(s);
    write (fd, s, size);
}

