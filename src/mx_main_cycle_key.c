 #include "header.h"

static void push_and_free(t_history_name **history, unsigned char **mystr, 
                    t_len_name *len, char *buf_first) {
    if ((*mystr)[0] != 0)
        mx_push_back_history(history, *mystr, len);
    if (len->first_line != true)
        free(buf_first);
}

static void read_and_width(t_len_name *len) {
    read (0, len->ch, 4);
    mx_get_width(&(len->col));
}

static bool check_for_byte(t_len_name *len) {
    if (len->ch[0] == 127 && len->ch[1] == 0 && len->ch[2] == 0
        && len->ch[3] == 0) {
            return true;
    }
    return false;
}



void mx_main_cycle_key(t_history_name **history, unsigned char **mystr, 
                       t_len_name *len, char *buf_first) {
    t_history_name *his = *history;

    while (1) {
        read_and_width(len);
        if (len->ch[0] != 27 && len->ch[0] != 9 ) {
            mx_one_cycle(mystr, len, len->buf);
            if (check_for_byte(len) == true)
                mx_back_to_str(mystr, &len);
            else if (len->ch[0] ==  10 || len->ch[0] == '\0') {
                mx_two_cycle(mystr, len);
                break;
            }
            else if (len->ch[0] != 27)
                mx_add_to_str(mystr, &len);
            mx_three_cycle(mystr, len);
        }
        mx_four_cycle(mystr, len, &buf_first, &his);
    }
    push_and_free(history, mystr, len, buf_first);
}
