 #include "header.h"

static void first_line_use(unsigned char **mystr, t_len_name *len,
                           char **buf_first) {
    if (len->first_line == false) {
        len->n_cursor = len->first_line_len;
        len->n_cursor_b = len->first_line_byte;
        len->n_len = len->first_line_len;
        len->n_bute = len->n_cursor_b;
        if (malloc_size(mystr))
            free(mystr);
        *mystr = (unsigned char *) strdup(*buf_first);
        fprintf(stdout, "%s", *mystr);
        fflush(stdout);
        len->first_line = true;
        len->trig_copy = false;
        len->first_line_len = 0;
        len->first_line_byte = 1;
    }
}

static void print_line(unsigned char **mystr, t_len_name *len, 
                       t_history_name **his) {
    (*his) = (*his)->previous;
    len->n_cursor = (*his)->n_len;
    len->n_cursor_b = (*his)->n_byte;
    len->n_len = len->n_cursor;
    len->n_bute = len->n_cursor_b;
    len->buf = (*his)->name;
    len->trig_copy = true;
    if (malloc_size(*mystr))
        free(*mystr);
    fprintf(stdout, "%s", (*his)->name);
    fflush(stdout);
}

void mx_arrow_down(unsigned char **mystr, t_len_name *len, char **buf_first,
                    t_history_name **his) {
    if (len->ch[0] == 27 && len->ch[1] == 91 && len->ch[2] == 66) {//errow down
        if (((*his) && (*his)->previous != NULL) || len->first_line == false) {
            if (len->n_cursor + 5 > len->col) {
                fprintf(stdout, "\033[%dF", (len->n_cursor + 4)/len->col);
                fflush(stdout);
            }
            else 
                mx_printstr("\033[1G");
            mx_printstr("\033[0J");
            mx_printstr("u$h> ");
            if ((*his)->previous != NULL)
                print_line(mystr, len, his);
            else
                first_line_use(mystr, len, buf_first);
        }
    }
}
