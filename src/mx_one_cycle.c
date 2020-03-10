 #include "header.h"

 
void mx_one_cycle(unsigned char **mystr, t_len_name *len, unsigned char *buf) {
    if (len->n_cursor + 5  > len->col) {
        fprintf(stdout, "\033[%dF", (len->n_cursor + 4)/len->col);
        fflush(stdout);
    }
    else
        mx_printstr("\033[1G");
    mx_printstr("\033[0J");
    mx_printstr("u$h> ");
    if (len->trig_copy == true) {
        if (malloc_size(*mystr))
            free(*mystr);
        *mystr = (unsigned char *)strdup((char *)buf);
        len->trig_copy = false;
    }
}
