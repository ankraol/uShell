 #include "header.h"

 
void mx_one_cycle(unsigned char **mystr, t_len_name *len, unsigned char *buf,
                 FILE *file) {
    //int file = open("/dev/tty", O_WRONLY);
    //  FILE *file = fopen("/dev/tty", "w");

    if (len->n_cursor + 5  > len->col) {
        fprintf(file, "\033[%dF", (len->n_cursor + 4)/len->col);
        fflush(file);
    }
    else
        fprintf(file, "\033[1G");
    fprintf(file, "\033[0J");
    fprintf(file, "u$h> ");
    fflush(file);
    //mx_printstr("\033[1G");
    //mx_printstr("\033[0J");
    //mx_printstr("u$h> ");
    if (len->trig_copy == true) {
        if (malloc_size(*mystr))
            free(*mystr);
        *mystr = (unsigned char *)strdup((char *)buf);
        len->trig_copy = false;
    }
}
