 #include "header.h"

void mx_two_cycle(unsigned char **mystr, t_len_name *len,
                    t_builtin_command *my_command) {
    if (len->ch[0] != '\n' || len->ch[0] == 4)
        len->trig = true;

    if (my_command->is_inp == true) {
        mx_printstr_fd((char *)*mystr, my_command->term_fg);
        mx_printstr_fd("\n", my_command->term_fg);
   }

    if (len->ch[0] == 4) {
        *mystr[0] = 4;
        *mystr[1] = 0;
    }
}

void mx_three_cycle(unsigned char **mystr, t_len_name *len, 
                    t_builtin_command *my_command) {
    if (my_command->is_inp == true) {
        mx_printstr_fd((char *)*mystr, my_command->term_fg);
        len->cur_pos_x = len->col - ((((len->n_cursor + 4)/len->col + 1) 
                        * len->col) - (len->n_cursor + 5)) + 1;
        if ((((len->n_len + 4)/len->col - (len->n_cursor + 4)/len->col)) > 0) {
            mx_printstr_fd("\033[", my_command->term_fg);
            mx_printint_fg(
                ((len->n_len + 4)/len->col - (len->n_cursor + 4)/len->col),
                my_command->term_fg);
            mx_printstr_fd("F", my_command->term_fg);
            mx_printstr_fd("\033[", my_command->term_fg);
            mx_printint_fg(len->cur_pos_x, my_command->term_fg);
            mx_printstr_fd("G", my_command->term_fg);
        }
        else {
            mx_printstr_fd("\033[", my_command->term_fg);
            mx_printint_fg(len->cur_pos_x, my_command->term_fg);
            mx_printstr_fd("G", my_command->term_fg);
        }
    }
}

