#include "header.h"

static void delete(t_len_name *len, char *buf_first){ 
    free(len);
    mx_strdel(&buf_first);
}

unsigned char *mx_read_line(t_builtin_command *my_command) {
    struct termios savetty;
    struct termios tty;
    t_len_name *len = mx_creat_len();
    unsigned char *mystr = (unsigned char *)malloc(sizeof(char) * 1);
    char *buf_first = NULL;

    mystr[0] = '\0';
    tcgetattr (0, &tty);
    savetty = tty;
    tty.c_lflag &= ~(ICANON | ECHO | ISIG);
    tty.c_cc[VMIN] = 1;
    tcsetattr(0, TCSAFLUSH, &tty);
    mx_get_width(&(len->col));
    if (my_command->is_inp) {
        fprintf(my_command->file, "u$h> ");
        fflush(my_command->file);
    }
    mx_main_cycle_key(my_command, &mystr, len, buf_first);
    tcsetattr (0, TCSAFLUSH, &savetty);
    my_command->trig = len->trig;
    delete(len, buf_first);
    return mystr;
}
