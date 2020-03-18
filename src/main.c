 #include "header.h"

static void exit_func(t_history_name **history, unsigned char *mystr, 
                      t_len_name *len, char *buf_first) {
    if (mx_strcmp("exit", mystr) == 0) {
        mx_delete_history(history);
        if (malloc_size(buf_first))
            free(buf_first);
        if (malloc_size(mystr))
            free(mystr);
        free(len);
        //system("leaks -q ush");
        exit(0);
    }
}

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
    tcsetattr (0, TCSAFLUSH, &savetty);
    exit_func(history, mystr, len, buf_first);
    *trig = len->trig;
    free(len); 
    return mystr;
}


static void build_export(t_export **export_list) {
    extern char **environ;
    char **full_val = NULL;
    
    if (environ != NULL) {
        for (int i = 0; environ[i] != NULL; i++) {
            full_val = mx_strsplit(environ[i], '=');
            if (full_val[0] != NULL)
                mx_push_back_export(export_list, full_val[0], full_val[1]);
            mx_del_strarr(&full_val);
        }
    }
}

void ush_loop(void) {
    unsigned char *line;
    int status = 2;
    t_queue **work = NULL;
    t_queue *p = NULL;
    bool trig = false;
    t_history_name *history = NULL;

    t_path_builtin pwd; 
    t_builtin_command my_command;
    //extern char **environ;

    my_command.unset_path = false;
    my_command.var = NULL;
    my_command.alias_list = NULL;

    pwd.pwdP = getcwd(NULL, 0);
    pwd.pwdL = getcwd(NULL, 0);
    pwd.oldpwd = getcwd(NULL, 0);

    my_command.cd = (t_cd *)malloc(sizeof(t_cd));
    memset(my_command.cd, 0, sizeof(t_cd));
    (&my_command)->pid_ar = NULL;

    
    my_command.export_ar = NULL;
    build_export(&(my_command.export_ar));
    //print_list(&(my_command.export_ar));



    while (trig == false) {
        // mx_printstr("u$h> ");
        line = mx_read_line(&trig, &history);
        if (line[0] != '\0') {
            work = mx_works_queue((char *)line);
            for (int i = 0; work[i]; i++) {
                p = work[i];
                for (; p; p = (*p).next) {
                    // printf("COMMAND BEFORE PARAMETER EXPANSION - %s\n", (*p).command);
                    (*p).command = mx_parameter_exp((*p).command, my_command.var);
                    // printf("COMMAND BEFORE SUBSTITUTION - %s\n", (*p).command);
                    (*p).command = mx_substitute((*p).command, &pwd, &my_command);
                    status = mx_redirection((*p).command, &pwd, &my_command);
                    if (((*p).op == '&' && status == 1)
                        || ((*p).op == '|' && status == 0))
                        {
                            p = (*p).next;
                        }
                }
            }
            // printf("NAME -> %s\n", aliasList->name);
            // printAlias(aliasList);
        }
        free(line);
        //system("leaks -q ush");
    }
}

void hdl(int sig)
{
    sig = sig + 1 - 1;
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
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);



    // signal(SIGTTIN, hdl);
    // signal(SIGTTOU, hdl);
    // signal(SIGQUIT, hdl);

    fprintf(stdout, "%d\n", getpid());
    fflush(stdout);

    ush_loop();
    //system("leaks -q ush");
    // lsh_loop();
    // mx_ush_pipe_execute(); 
    
}


