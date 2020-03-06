 #include "header.h"

t_len_name *mx_creat_len() {
    t_len_name *len = (t_len_name *)malloc(sizeof(t_len_name) * 1);

    len->n_bute = 1;
    len->n_len = 0;
    len->n_cursor = 0;
    len->cur_pos_x = 0;
    len->n_cursor_b = 1;
    len->col = 0;
    len->cursor_delta_len = 1;
    len->cursor_delta_b = 0;
    len->first_line = true;
    len->first_line_len = 0;
    len->first_line_byte = 1;
    len->trig = false;
    len->trig_copy = false;
    len->buf = NULL;
    return len;
}

