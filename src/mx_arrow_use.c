#include "header.h"

static void first(unsigned char **mystr, t_len_name *len) {
    if (len->trig_copy == true) {
        *mystr = (unsigned char *)strdup((char *)len->buf);
        len->trig_copy = false;
    }
}

void mx_arrow_left(unsigned char **mystr, t_len_name *len, int term_fd) {
    if (len->ch[0] == 27 && len->ch[1] == 91 && len->ch[2] == 68) {//errow left
        if (len->n_cursor > 0) {
            first(mystr, len);
            mx_byte_check_back(*mystr, &(len->cursor_delta_len), 
                               &(len->cursor_delta_b), len->n_cursor_b);
            len->cur_pos_x = len->cur_pos_x - len->cursor_delta_len;
            len->n_cursor = len->n_cursor - len->cursor_delta_len;
            len->n_cursor_b = len->n_cursor_b - len->cursor_delta_b;
            len->cursor_delta_len = 1;
            if (len->cur_pos_x < 1) {
                mx_printstr_fd("\033[", term_fd);
                mx_printint_fg(1, term_fd);
                mx_printstr_fd("F", term_fd);

                mx_printstr_fd("\033[", term_fd);
                mx_printint_fg(len->col, term_fd);
                mx_printstr_fd("G", term_fd);

                //fprintf(file, "\033[%dF",1);
                //fprintf(file, "\033[%dG", len->col);
                len->cur_pos_x = len->col;
            }
            else {

                mx_printstr_fd("\033[", term_fd);
                mx_printint_fg(len->cur_pos_x, term_fd);
                mx_printstr_fd("G", term_fd);

                //fprintf(file, "\033[%dG", len->cur_pos_x);

            }
            //fflush(file);
        }
    }
}

void mx_arrow_right(unsigned char **mystr, t_len_name *len, int term_fd) {
    if (len->ch[0] == 27 && len->ch[1] == 91 && len->ch[2] == 67) {//errowright
        if (len->n_cursor < len->n_len) {
            mx_byte_check_add(*mystr, &(len->cursor_delta_len),
                              &(len->cursor_delta_b), len->n_cursor_b);
            len->cur_pos_x = len->cur_pos_x + len->cursor_delta_len;
            len->n_cursor = len->n_cursor + len->cursor_delta_len;
            len->n_cursor_b = len->n_cursor_b + len->cursor_delta_b;
            len->cursor_delta_len = 1;
            if (len->cur_pos_x > len->col) {
                mx_printstr_fd("\033[", term_fd);
                mx_printint_fg(1, term_fd);
                mx_printstr_fd("E", term_fd);

                mx_printstr_fd("\033[", term_fd);
                mx_printint_fg(1, term_fd);
                mx_printstr_fd("G", term_fd);

                //fprintf(file, "\033[%dE",1);
                //fprintf(file, "\033[%dG", 1);
                len->cur_pos_x = 1;
            }
            else {
                mx_printstr_fd("\033[", term_fd);
                mx_printint_fg(len->cur_pos_x, term_fd);
                mx_printstr_fd("G", term_fd);
                //fprintf(file, "\033[%dG", len->cur_pos_x);

            }
            //fflush(file);
        }
    }
}
