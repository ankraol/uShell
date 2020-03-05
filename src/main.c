 #include "header.h"

unsigned char *mx_read_line(bool *trig, t_history_name **history) {
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
    tcsetattr (0, TCSAFLUSH, &tty);
    mx_get_width(&(len->col));
    mx_printstr("u$h> ");
    mx_main_cycle_key(history, &mystr, len, buf_first);
    *trig = len->trig;
    free(len);
    tcsetattr (0, TCSAFLUSH, &savetty);
    return mystr;
}


void ush_loop(void) {
    unsigned char *line;
    int status = 2;
    t_queue **work = NULL;
    t_queue *p = NULL;
    bool trig = false;

    t_history_name *history = NULL;

    t_path_builtin pwd; 
    //= malloc(sizeof(t_path_builtin));
    // memset(pwd, 0, sizeof(t_path_builtin));

    pwd.pwdP = getcwd(NULL, 0);
    pwd.pwdL = getcwd(NULL, 0);
    pwd.oldpwd = getcwd(NULL, 0);


    while (trig == false) {
        // mx_printstr("u$h> ");
        line = mx_read_line(&trig, &history);
       
        if (line[0] != '\0') {

            work = mx_works_queue((char *)line);
            for (int i = 0; work[i]; i++) {
                p = work[i];
                for (; p; p = (*p).next) {
                    (*p).command = mx_parameter_exp((*p).command);
                    (*p).command = mx_substitute((*p).command);
                    status = mx_redirection((*p).command);
                    if (((*p).op == '&' && status == 1)
                        || ((*p).op == '|' && status == 0))
                        {
                            p = (*p).next;
                        }

        // fprintf(stdout, "%s", line);
        // fflush(stdout);
        work = mx_works_queue((char *)line);
        for (int i = 0; work[i]; i++) {
            p = work[i];
            for (; (*p).right_child; p = (*p).right_child);
            if ((*p).parent) {
                p = (*p).parent;
                status = mx_redirection((*(*p).right_child).command, &pwd);
                // printf("\n\nSTATUS = %d\n\n\n", status);
                // if (status == 2)
                    // status = mx_ush_execute((*(*p).right_child).command);
                for (; p != NULL; p = (*p).parent) {
                    if ((*p).operant[1] == '|') {
                        if (status == 1) {
                            status = mx_redirection((*(*p).left_child).command, &pwd);
                            // printf("\n\nSTATUS = %d\n\n\n", status);
                            // if (status == 2)
                                // status = mx_ush_execute((*(*p).left_child).command);
                        }
                        else if ((*p).operant[1] == '&') {
                            if (status == 0) {
                                status = mx_redirection((*(*p).left_child).command, &pwd);
                                // printf("\n\nSTATUS = %d\n\n\n", status);
                                // if (status == 2)
                                    // status = mx_ush_execute((*(*p).left_child).command);
                            }
                        }
                    }
                }
            }
                else
                {
                    status = mx_redirection((*p).command, &pwd);
                    // printf("\n\nSTATUS = %d\n\n\n", status);
                    // if (status == 2)
                        // status = mx_ush_execute((*p).command);

                }
            }
        }
        free(line);
        //system("leaks -q ush");
    }
}

void hdl(int sig)
{
    sig = sig +1 - 1;
    // printf("%d - pid\n", getpid());
    //printf("\n");
}

int main(void) {
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



    ush_loop();
    //system("leaks -q ush");
    // lsh_loop();
    // mx_ush_pipe_execute(); 
    
}


