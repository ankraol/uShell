 #include "header.h"

#include <stdlib.h>

// char *mx_read_line() {
//     char c;
//     int bufsize = 1024;
//     int position = 0;
//     char *buffer = (char *)malloc(sizeof(char) * bufsize);

//     while(1) {
//         c = getchar();
//         if (c == '\0' || c == '\n') {
//             buffer[position] = '\0';
//             return buffer;
//         }
//         else {
//             buffer[position] = c;
//         }
//         position++;
//     }
// }

void add_to_str(char **str, char c, int *n) {
    (*n) += 1;
    (*str) = (char *)realloc(*str, (*n));
    (*str)[(*n) - 1] = '\0';
    (*str)[(*n) - 2] = c;
    //*(str[n+1]) = '\0';
}

void back_to_str(char **str, int *n) {
    if ((*n) > 1) {
        (*str)[(*n) - 2] = '\0';
        (*n) -= 1;
        (*str) = (char *)realloc(*str, (*n));
    }
}



char *mx_read_line() {
    struct termios savetty;
    struct termios tty;
    char ch = 0;
    char *mystr = (char *)malloc(sizeof(char) * 1);
    mystr[0] = '\0';
    int n = 1;

    tcgetattr (0, &tty);
    savetty = tty; /* Сохранить упр. информацию канонического режима */
    tty.c_lflag &= ~(ICANON | ECHO | ISIG);
    tty.c_cc[VMIN] = 1;
    tcsetattr (0, TCSAFLUSH, &tty);

    mx_printstr("\x1B[s");
    
    mx_printstr("u$h> ");

 
    while (1) {

        read (0, &ch, 1);
        // mx_printstr("u$h> ");
        mx_printstr("\x1B[u");
        mx_printstr("\x1B[0K");
        //read (0, &ch, 1);

 
        if (ch == 127)
            back_to_str(&mystr, &n);
        else if (ch == '\n') {
            mx_printstr("u$h> ");
            mx_printstr(mystr);
            write(1, "\n", 1);
            if (strcmp("exit", mystr) == 0)
                exit(0);
            break;
        }
        else 
            add_to_str(&mystr, ch, &n);

        //mx_printstr(mx_itoa(ch));
        mx_printstr("u$h> ");
        mx_printstr(mystr);
        // if (ch != 'n')
        //     write(1, "\n", 1);
    }

    tcsetattr (0, TCSAFLUSH, &savetty);
    return mystr;
}


void lsh_loop(void) {
    char *line;
    int status = 2;
    t_tree *work = NULL;
    t_tree *p = NULL;

    while (1) {
        
        line = mx_read_line();
        work = mx_parcing(line);
        p = work;
        for (; (*p).right_child; p = (*p).right_child);
        if ((*p).parent) {
            p = (*p).parent;
            status = mx_redirection((*(*p).right_child).command);
            // printf("\n\nSTATUS = %d\n\n\n", status);
            // if (status == 2)
                // status = mx_ush_execute((*(*p).right_child).command);
            for (; p != NULL; p = (*p).parent) {
                if ((*p).operant[1] == '|') {
                    if (status == 1) {
                        status = mx_redirection((*(*p).left_child).command);
                        // printf("\n\nSTATUS = %d\n\n\n", status);
                        // if (status == 2)
                            // status = mx_ush_execute((*(*p).left_child).command);
                    }
                }
                else if ((*p).operant[1] == '&') {
                    if (status == 0) {
                        status = mx_redirection((*(*p).left_child).command);
                        // printf("\n\nSTATUS = %d\n\n\n", status);
                        // if (status == 2)
                            // status = mx_ush_execute((*(*p).left_child).command);
                    }
                }
            }
        }
        else
        {
            status = mx_redirection((*p).command);
            // printf("\n\nSTATUS = %d\n\n\n", status);
            // if (status == 2)
                // status = mx_ush_execute((*p).command);
        }
        free(line);
    }
}
void hdl(int sig)
{
    sig = sig +1 - 1;
    // printf("%d - pid\n", getpid());
    //printf("\n");
}

int main() {
    // struct sigaction act;
    // memset(&act, 0, sizeof(act));
    // act.sa_handler = hdl;
    // sigset_t set;
    // sigemptyset(&set);
    // act.sa_mask = set;
    // sigaddset(&set, SIGINT);
    // sigaddset(&set, SIGTSTP);
    

    // act.sa_mask = set;
    // sigaction(SIGINT, &act, 0);
    // sigaction(SIGTSTP, &act, 0);

    signal(SIGINT, hdl);
    signal(SIGTSTP, hdl);



    // signal(SIGTTIN, hdl);
    // signal(SIGTTOU, hdl);
    // signal(SIGQUIT, hdl);



    lsh_loop();
    // lsh_loop();
    // mx_ush_pipe_execute(); 
    
}


