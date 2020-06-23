 #include "header.h"

void mx_printint_fg(int n, int fd) {
	if ( n == -2147483648)
        write(fd, "-2147483648", 11);
	else {
		if (n < 0) {
			n = n * -1;
			mx_printchar_fd('-', fd);
		}
		if (n/10 >= 1) {
			mx_printint_fg(n/10, fd);
		}
		mx_printchar_fd(n%10+48, fd);
	}
}
