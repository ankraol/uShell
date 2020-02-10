 #include "header.h"

char *mx_read_line() {
    char c;
    int bufsize = 1024;
    int position = 0;
    char *buffer = (char *)malloc(sizeof(char) * bufsize);

    while(1) {
        c = getchar();
        if (c == '\0' || c == '\n') {
            buffer[position] = '\0';
            return buffer;
        }
        else {
            buffer[position] = c;
        }
        position++;
    }
}

void lsh_loop(void) {
    char *line;
    int status = 2;
    t_tree *work = NULL;
    t_tree *p = NULL;

    while (1) {
        printf("super_shell: ");
        line = mx_read_line();
        work = mx_parcing(line);
        p = work;
        for (; (*p).right_child; p = (*p).right_child);
        if ((*p).parent) {
            p = (*p).parent;
            status = mx_redirection((*(*p).right_child).command);
            // if (status == 2)
                // status = mx_ush_execute((*(*p).right_child).command);
            for (; p != NULL; p = (*p).parent) {
                if ((*p).operant[1] == '|') {
                    if (status == 1) {
                        status = mx_redirection((*(*p).left_child).command);
                        // if (status == 2)
                            // status = mx_ush_execute((*(*p).left_child).command);
                    }
                }
                else if ((*p).operant[1] == '&') {
                    if (status == 0) {
                        status = mx_redirection((*(*p).left_child).command);
                        // if (status == 2)
                            // status = mx_ush_execute((*(*p).left_child).command);
                    }
                }
            }
        }
        else
        {
            status = mx_redirection((*p).command);
            // if (status == 2)
                // status = mx_ush_execute((*p).command);
        }
        free(line);
    }
}


int main() {
    lsh_loop();
    // lsh_loop();
    // mx_ush_pipe_execute(); 
    
}


