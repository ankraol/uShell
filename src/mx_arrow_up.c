#include "header.h"

static void first_line_use(unsigned char **mystr, t_len_name *len,
                           char **buf_first) {
    if (len->first_line == true) {
        len->first_line_len = len->n_len;
        len->first_line_byte = len->n_bute;
        if (*buf_first != NULL && malloc_size(*buf_first)) 
                free(*buf_first);
        if (*mystr != NULL && malloc_size(*mystr)) {
            *buf_first = strdup((char *) *mystr);
            free(*mystr);
            *mystr = NULL;
        }
        else {
            *buf_first = (char *)malloc(sizeof(char) * 1);
            (*buf_first)[0] = '\0';
        }
        len->first_line = false;
    }
}

static void print_line(unsigned char **mystr, t_len_name *len, 
                       t_history_name **his) {
    mx_printstr("\033[0J");
    mx_printstr("u$h> ");
    len->n_cursor = (*his)->n_len;
    len->n_cursor_b = (*his)->n_byte;
    len->n_len = len->n_cursor;
    len->n_bute = len->n_cursor_b;
    len->buf = (*his)->name;
    len->trig_copy = true;
    if (malloc_size(*mystr) && *mystr != NULL)
        free(*mystr);
    fprintf(stdout, "%s", (*his)->name);
    fflush(stdout);
    if ((*his)->next)
        (*his) = (*his)->next;
}

void mx_arrow_up(unsigned char **mystr, t_len_name *len, char **buf_first,
                t_history_name **his) {
    if (len->ch[0] == 27 && len->ch[1] == 91 && len->ch[2] == 65) {// errow up
        if (*his != NULL) {
            first_line_use(mystr, len, buf_first);
            if (len->n_cursor + 5 > len->col) {
                fprintf(stdout, "\033[%dF", (len->n_cursor + 4)/len->col);
                fflush(stdout);
            }
            else
                mx_printstr("\033[1G");
            print_line(mystr, len, his);
        }
    }
}
