 #include "header.h"

void mx_two_cycle(t_history_name **history, unsigned char **mystr, 
                t_len_name *len, char *buf_first) {

    if (len->ch[0] != '\n') 
            len->trig = true;
    fprintf(stdout, "%s", *mystr);
    fflush(stdout);
    write(1, "\n", 1);
    if (mx_strcmp("exit", *mystr) == 0) {
        mx_delete_history(history);
        if (malloc_size(buf_first))
            free(buf_first);
        if (malloc_size(*mystr))
            free(*mystr);
        free(len);
        exit(0);
    }
}

void mx_three_cycle(unsigned char **mystr, t_len_name *len) {
    fprintf(stdout, "%s", *mystr);
    fflush(stdout);
    len->cur_pos_x = len->col - ((((len->n_cursor + 4)/len->col + 1) 
                     * len->col) - (len->n_cursor + 5)) + 1;
    if ((((len->n_len + 4)/len->col - (len->n_cursor + 4)/len->col)) > 0) {
        fprintf(stdout, "\033[%dF", 
                ((len->n_len + 4)/len->col - (len->n_cursor + 4)/len->col));
        fprintf(stdout, "\033[%dG", len->cur_pos_x);
        fflush(stdout);
    }
    else {
        fprintf(stdout, "\033[%dG", len->cur_pos_x);
        fflush(stdout);
    }
}

