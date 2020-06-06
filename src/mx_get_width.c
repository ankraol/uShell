 #include "header.h"

void mx_get_width(int *col) {
    // char *termtype = getenv("TERM");
    // char *buff = malloc(2048);
    int success = 0;
    // bool if_term = 0;

    // if (termtype == 0) {
        // termtype = mx_strdup();
    //     if_term = 1;
    // }

    if ((success = tgetent(NULL, "xterm-256color")) < 0) {
        //fprintf(stderr, "%s", MX_ETGTN);
        // free(buff);
        exit(1);
    }
    // free(buff);
    // if (if_term)
    //     mx_strdel(&termtype);
    *col = tgetnum("co");
    //printf("-------%d\n", *col);


    //*col = 80;
}
