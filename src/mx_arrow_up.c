#include "header.h"

static void first_line_use(unsigned char **mystr, t_len_name *len,
                           char **buf_first) {
    if (len->first_line == true) {
        len->first_line_len = len->n_len;
        len->first_line_byte = len->n_bute;
        if (*buf_first != NULL && malloc_size(*buf_first))
            free(*buf_first);
        if (*mystr != NULL && malloc_size(*mystr)) {
            *buf_first = strdup((char *)*mystr);
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

static void print_line(t_len_name *len, t_history_name **his, FILE *file) {
    fprintf(file, "\033[0J");
    fprintf(file, "u$h> ");
    len->n_cursor = (*his)->n_len;
    len->n_cursor_b = (*his)->n_byte;
    len->n_len = len->n_cursor;
    len->n_bute = len->n_cursor_b;
    len->buf = (*his)->name;
    len->trig_copy = true;
    // if (*mystr != NULL && malloc_size(*mystr))
    //     free(*mystr);
    fprintf(file, "%s", (*his)->name);
    fflush(file);
    if ((*his)->next)
        (*his) = (*his)->next;
}

void mx_arrow_up(unsigned char **mystr, t_len_name *len, char **buf_first,
                t_builtin_command *my_com) {
    if (len->ch[0] == 27 && len->ch[1] == 91 && len->ch[2] == 65) {// errow up
        if (my_com->his != NULL) {
            first_line_use(mystr, len, buf_first);
            if (len->n_cursor + 5 > len->col) {
                fprintf(my_com->file, "\033[%dF", (len->n_cursor + 4)/len->col);
                //fflush(file);
            }
            else
                fprintf(my_com->file, "\033[1G");
            fflush(my_com->file);
            print_line(len, &(my_com->his), my_com->file);
        }
    }
}
