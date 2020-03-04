 #include "header.h"

void mx_get_width(int *col) {
    char *termtype = getenv("TERM");
    char *buff = malloc(2048);
    bool if_term = 0;

    if (termtype == 0) {
        termtype = strdup("xterm-256color");
        if_term = 1;
    }
    if (tgetent (buff, termtype) == 0) {
        perror("ush: ");
        exit(1);
    }
    free(buff);
    if (if_term)
        mx_strdel(&termtype);
    *col = tgetnum("co");
}
