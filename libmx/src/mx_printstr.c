#include "libmx.h"

void mx_printstr(const char *s) {
	int size = mx_strlen(s);
    write (1, s, size);
}

