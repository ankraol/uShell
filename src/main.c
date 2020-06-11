#include "header.h"

static void exit_func(t_builtin_command *my_command) {
    //if (mx_strcmp("exit", mystr) == 0 || mystr[0] == 4) {
        mx_delete_history(&(my_command->history));
        printf("\nTEST EXIT/\n");
    //}
}

static bool contral_d(unsigned char **str, t_builtin_command *my_command) {
    if (*str[0] == 4) {
        my_command->trig = true;
        mx_strdel((char **) str);
        return true;
    }
    return false;
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
    fprintf(my_command->file, "u$h> ");
    fflush(my_command->file);
    mx_main_cycle_key(my_command, &mystr, len, buf_first);
    tcsetattr (0, TCSAFLUSH, &savetty);
    my_command->trig = len->trig;
    free(len);
    mx_strdel(&buf_first);
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

    if (*work != NULL) {
        for (int i = 0; (*work)[i]; i++) {
            p = (*work)[i];
            while (p) {
                //printf("DELETE : %s\n", p->command);
                buf = p->next;
                mx_strdel(&(p->command));
                if (malloc_size(p) && p != NULL)
                    free(p);
                p = buf;
            }
        }
        if (malloc_size(*work) && *work != NULL) {
            free(*work);
            *work = NULL;
        }
    }

}

// static void work_print(t_queue **work) {
//     t_queue *p = NULL;
    
//     for (int i = 0; work[i]; i++) {
//         for (p = work[i]; p; p = p->next) {
//             printf("COMMAND AFTER WORK_QUEUE = %s\n", p->command);
//         }
//     }
// }

int ush_loop(void) {
    unsigned char *line;
   int status = 2;
   t_queue **work = NULL;
   t_queue *p = NULL;
    int exit_code = 0;



//    t_path_builtin pwd;
    t_builtin_command my_command;
    my_command.trig = false;
    my_command.exit_code = 0;


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





    while (my_command.trig == false) {
        // mx_printstr("u$h> ");
        line = mx_read_line(&my_command);
        // mx_printstr((char *) line);
        // mx_printstr("\n");
        //contral_d(&line, &my_command);
        //printf("HERE\n");
        //printf("%-----d-----\n", line[0]);
        //system("leaks -q ush");
        if (line && line[0] != '\0' && !contral_d(&line, &my_command)) {

            // printf("BEFORE WORK SPLIT - %s\n", line);
            work = mx_works_queue((char *)line);
            //work_print(work);
            //system("leaks -q ush");
            for (int i = 0; work[i]; i++) {
                p = work[i];
                for (; p; p = (*p).next) {
                    printf("COMMAND BEFORE PARAMETER EXPANSION - %s\n", (*p).command);
                    (*p).command = mx_expandParameter((*p).command, my_command.var);
                    // system("leaks -q ush");
                    printf("COMMAND BEFORE SUBSTITUTION - %s\n", (*p).command);
                    (*p).command = mx_substitute((*p).command, &my_command);
                    printf("COMMAND AFTER SUBSTITUTION - %s\n", (*p).command);
                //    system("leaks -q ush");
                    status = mx_redirection((*p).command, &my_command);
                    printf("COMMAND AFTER REDIRECTION - %s\n", (*p).command);
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
        //printf("del work\n");
        exit_code = my_command.exit_code;
        del_work(&work);
        //printf("del line\n");
        free(line);
        system("leaks -q ush");
    }
    exit_func(&my_command);
    //system("leaks -q ush");
    return exit_code;
}

void hdl(int sig)
{
    sig = sig + 1 - 1;
    // printf("%d - pid\n", getpid());
    //printf("\n");
}

int main(void) {
    int exit = 0;
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

    exit = ush_loop();
    return exit;
    //system("leaks -q ush");
    // lsh_loop();
    // mx_ush_pipe_execute(); 
    //system("leaks -q ush");
    
}


