 #include "header.h"

void mx_four_cycle(unsigned char **mystr, t_len_name *len, char **buf_first,
                   t_history_name **his) {
    len->cur_pos_x = len->col - ((((len->n_cursor + 5)/len->col + 1) 
                    * len->col) - (len->n_cursor + 5)) + 1;
    mx_arrow_left(mystr, len);
    mx_arrow_right(mystr, len);
    mx_arrow_up(mystr, len, buf_first, his);
    mx_arrow_down(mystr, len, buf_first, his);
    len->ch[0] = 0;
    len->ch[1] = 0;
    len->ch[2] = 0;
    len->ch[3] = 0;
}