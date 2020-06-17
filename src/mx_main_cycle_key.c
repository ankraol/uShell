 #include "header.h"

static void push_and_free(t_history_name **history, unsigned char **mystr, 
                    t_len_name *len, char *buf_first) {
    if ((*mystr)[0] != 0)
        mx_push_back_history(history, *mystr, len);
    if (len->first_line != true)
        free(buf_first);
}

static void read_and_width(t_len_name *len, t_builtin_command *my_command) {
    if (my_command->is_inp)
        read (0, len->ch, 4);
    else
        read (0, len->ch, 1);
    mx_get_width(&(len->col));
}

static bool check_for_byte(t_len_name *len) {
    if (len->ch[0] == 127 && len->ch[1] == 0 && len->ch[2] == 0
        && len->ch[3] == 0) {
            return true;
    }
    return false;
}

void mx_main_cycle_key(t_builtin_command *my_command, unsigned char **mystr, 
                       t_len_name *len, char *buf_first) {
    my_command->his = my_command->history;

    while (1) {
        read_and_width(len, my_command);
        if (len->ch[0] != 27 && len->ch[0] != 9 ) {
            mx_one_cycle(mystr, len, len->buf, my_command);
            if (check_for_byte(len) == true)
                mx_back_to_str(mystr, &len);
            else if ((len->ch[0] ==  10 || len->ch[0] == '\0') ||
                    (len->ch[0] == 4 && *mystr[0] == 0)) {
                mx_two_cycle(mystr, len, my_command->file, my_command);
                break;
            }
            else if (len->ch[0] >= 32)
                mx_add_to_str(mystr, &len);
            mx_three_cycle(mystr, len, my_command->file, my_command);
        }
        mx_four_cycle(mystr, len, &buf_first, my_command);
    }
    push_and_free(&(my_command->history), mystr, len, buf_first);
}
