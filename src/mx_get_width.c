 #include "header.h"

void mx_get_width(int *col) {
    int success = 0;

    if ((success = tgetent(NULL, "xterm-256color")) < 0)
        exit(1);
    *col = tgetnum("co");
}
