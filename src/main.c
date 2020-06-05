#include "header.h"

static void exit_func(t_history_name **history, unsigned char *mystr, 
                      t_len_name *len, char *buf_first) {
    if (mx_strcmp("exit", mystr) == 0 || mystr[0] == 4) {
        mx_delete_history(history);
        if (malloc_size(buf_first))
            free(buf_first);
        if (malloc_size(mystr))
            free(mystr);
        free(len);
        printf("\nTEST EXIT/\n");
        //system("leaks -q ush");
        exit(0);
    }
}

unsigned char *mx_read_line(bool *trig, t_builtin_command *my_command) {
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
    fprintf(my_command->file, "u$h> ");
    fflush(my_command->file);
    mx_main_cycle_key(my_command, &mystr, len, buf_first);
    tcsetattr (0, TCSAFLUSH, &savetty);
    exit_func(&(my_command->history), mystr, len, buf_first);
    *trig = len->trig;
    free(len); 
    return mystr;
}

void mx_mysetenv() {
    struct passwd *pw = getpwuid(getuid());
    char *pwd = getcwd(NULL, 0);
    setenv("HOME", pw->pw_dir, 0);
    setenv("LOGNAME", getlogin(), 0);
    setenv("PWD", pwd, 0);
    setenv("OLDPWD",pwd, 0);
    setenv("SHLVL", "1", 0);
    setenv("_", "/usr/bin/env", 0);
    free(pwd);
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

void del_work( t_queue ***work) {
    t_queue *p = NULL;
    t_queue *buf = NULL;

    for (int i = 0; (*work)[i]; i++) {
        p = (*work)[i];
        while (p) {
           buf = p->next;
           mx_strdel(&(p->command));
           free(p);
           p = buf;
        }
    }
    free(*work);
    
}


void ush_loop(void) {
    unsigned char *line;
   int status = 2;
   t_queue **work = NULL;
   t_queue *p = NULL;
    bool trig = false;


//    t_path_builtin pwd;
    t_builtin_command my_command;


    my_command.unset_path = false;
    my_command.var = NULL;
    my_command.alias_list = NULL;

    my_command.path = (t_path_builtin *)malloc(sizeof(t_path_builtin));
    my_command.path->pwdP = getcwd(NULL, 0);
    my_command.path->pwdL = getcwd(NULL, 0);
    my_command.path->oldpwd = getcwd(NULL, 0);

    my_command.cd = (t_cd *)malloc(sizeof(t_cd));
    memset(my_command.cd, 0, sizeof(t_cd));

    my_command.echo = (t_echo *)malloc(sizeof(t_echo));
    memset(my_command.echo, 0, sizeof(t_echo));

    (&my_command)->pid_ar = NULL;
    mx_mysetenv();



    (&my_command)->history = NULL;
    my_command.his = NULL;
    my_command.export_ar = NULL;
    my_command.file = fopen("/dev/tty", "w");
    build_export(&(my_command.export_ar));




    while (trig == false) {
        // mx_printstr("u$h> ");
        line = mx_read_line(&trig, &my_command);
        //system("leaks -q ush");
        if (line[0] != '\0') {
            printf("BEFORE WORK SPLIT - %s\n", line);
            work = mx_works_queue((char *)line);
            system("leaks -q ush");
            for (int i = 0; work[i]; i++) {
                p = work[i];
                for (; p; p = (*p).next) {
                    // printf("COMMAND BEFORE PARAMETER EXPANSION - %s\n", (*p).command);
                    //(*p).command = mx_parameter_exp((*p).command, my_command.var);
                    // system("leaks -q ush");
                    printf("COMMAND BEFORE SUBSTITUTION - %s\n", (*p).command);
                    (*p).command = mx_substitute((*p).command, &my_command);
                    printf("everything is ok ---- %s\n", (*p).command);
                   // system("leaks -q ush");
                    status = mx_redirection((*p).command, &my_command);
                   // system("leaks -q ush");
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
        del_work(&work);
        free(line);
        // system("leaks -q ush");
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

   // fprintf(stdout, "%d\n", getpid());
   // fflush(stdout);

    ush_loop();
    //system("leaks -q ush");
    // lsh_loop();
    // mx_ush_pipe_execute(); 
    //system("leaks -q ush");
    
}


