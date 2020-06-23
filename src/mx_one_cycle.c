 #include "header.h"

 
void mx_one_cycle(unsigned char **mystr, t_len_name *len, unsigned char *buf,
                 t_builtin_command *my_command) {

    if (len->n_cursor + 5  > len->col) {
        mx_printstr_fd("\033[", my_command->term_fg);
        mx_printint_fg((len->n_cursor + 4)/len->col, my_command->term_fg);
        mx_printstr_fd("F", my_command->term_fg);

        //fprintf(my_command->file, "\033[%dF", (len->n_cursor + 4)/len->col);
        //fflush(my_command->file);
    }
    else {
        mx_printstr_fd("\033[1G", my_command->term_fg);
        //fprintf(my_command->file, "\033[1G");
    
    }
    mx_printstr_fd("\033[0J", my_command->term_fg);
    //fprintf(my_command->file, "\033[0J");
    if (my_command->is_inp) {
        mx_printstr_fd("u$h> ", my_command->term_fg);
        //fprintf(my_command->file, "u$h> ");
        //fflush(my_command->file);
    }
    if (len->trig_copy == true) {
        if (malloc_size(*mystr))
            free(*mystr);
        *mystr = (unsigned char *)strdup((char *)buf);
        len->trig_copy = false;
    }
}
