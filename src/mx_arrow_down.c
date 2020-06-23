 #include "header.h"

static void first_line_use(unsigned char **mystr, t_len_name *len,
                           char **buf_first, int term_fg) {
    if (len->first_line == false) {
        len->n_cursor = len->first_line_len;
        len->n_cursor_b = len->first_line_byte;
        len->n_len = len->first_line_len;
        len->n_bute = len->n_cursor_b;
        if (malloc_size(*mystr))
            free(*mystr);
        *mystr = (unsigned char *) strdup(*buf_first);
        mx_printstr_fd((char *)*mystr, term_fg);
        // fprintf(file, "%s", *mystr);
        // fflush(file);
         if (malloc_size(*buf_first))
            free(*buf_first);
        len->first_line = true;
        len->trig_copy = false;
        len->first_line_len = 0;
        len->first_line_byte = 1;
    }
}

static void print_line(t_len_name *len, t_history_name **his, int term_fg) {
    (*his) = (*his)->previous;
    len->n_cursor = (*his)->n_len;
    len->n_cursor_b = (*his)->n_byte;
    len->n_len = len->n_cursor;
    len->n_bute = len->n_cursor_b;
    len->buf = (*his)->name;
    len->trig_copy = true;
    mx_printstr_fd((char *)(*his)->name, term_fg);
    // fprintf(file, "%s", (*his)->name);
    // fflush(file);
}

void mx_arrow_down(unsigned char **mystr, t_len_name *len, char **buf_first,
                    t_builtin_command *my_co) {
    if (len->ch[0] == 27 && len->ch[1] == 91 && len->ch[2] == 66) {//errow down
        if ((my_co->his && my_co->his->previous != NULL)
            || len->first_line == false) {
            if (len->n_cursor + 5 > len->col) {

                mx_printstr_fd("\033[", my_co->term_fg);
                mx_printint_fg((len->n_cursor + 4)/len->col, my_co->term_fg);
                mx_printstr_fd("F", my_co->term_fg);

                // fprintf(my_co->file, "\033[%dF", (len->n_cursor + 4)/len->col);
                // fflush(my_co->file);
            }
            else {
                mx_printstr_fd("\033[1G", my_co->term_fg);
                //fprintf(my_co->file, "\033[1G");
            }
            mx_printstr_fd("\033[0J", my_co->term_fg);
            mx_printstr_fd("u$h> ", my_co->term_fg);
            //fprintf(my_co->file, "\033[0J");
            //fprintf(my_co->file, "u$h> ");
            if (my_co->his->previous != NULL)
                print_line(len, &(my_co->his), my_co->term_fg);
            else
                first_line_use(mystr, len, buf_first, my_co->term_fg);
        }
    }
}
