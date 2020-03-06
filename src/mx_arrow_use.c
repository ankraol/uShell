#include "header.h"

void mx_arrow_left(unsigned char **mystr, t_len_name *len) {
    if (len->ch[0] == 27 && len->ch[1] == 91 && len->ch[2] == 68) {//errow left
        if (len->n_cursor > 0) {
            mx_byte_check_back(*mystr, &(len->cursor_delta_len), 
                               &(len->cursor_delta_b), len->n_cursor_b);
            len->cur_pos_x = len->cur_pos_x - len->cursor_delta_len;
            len->n_cursor = len->n_cursor - len->cursor_delta_len;
            len->n_cursor_b = len->n_cursor_b - len->cursor_delta_b;
            len->cursor_delta_len = 1;
            if (len->cur_pos_x < 1) {
                fprintf(stdout, "\033[%dF",1);
                fprintf(stdout, "\033[%dG", len->col);
                len->cur_pos_x = len->col;
            }
            else
                fprintf(stdout, "\033[%dG", len->cur_pos_x);
            fflush(stdout);
        }
    }
}

void mx_arrow_right(unsigned char **mystr, t_len_name *len) {
    if (len->ch[0] == 27 && len->ch[1] == 91 && len->ch[2] == 67) {//errowright
        if (len->n_cursor < len->n_len) {
            mx_byte_check_add(*mystr, &(len->cursor_delta_len), 
                              &(len->cursor_delta_b), len->n_cursor_b);
            len->cur_pos_x = len->cur_pos_x + len->cursor_delta_len;
            len->n_cursor = len->n_cursor + len->cursor_delta_len;
            len->n_cursor_b = len->n_cursor_b + len->cursor_delta_b;
            len->cursor_delta_len = 1;
            if (len->cur_pos_x > len->col) {
                fprintf(stdout, "\033[%dE",1);
                fprintf(stdout, "\033[%dG", 1);
                len->cur_pos_x = 1;
            }
            else 
                fprintf(stdout, "\033[%dG", len->cur_pos_x);
            fflush(stdout);
        }
    }
}
