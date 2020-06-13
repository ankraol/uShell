#include "header.h"

static void exit_func(t_builtin_command *my_command) {
    mx_delete_history(&(my_command->history));
    printf("\nTEST EXIT/\n");
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
    if (getenv("SHLVL") != NULL) {
        char *num = getenv("SHLVL");
        *num += 1;
        setenv("SHLVL", num, 1);
    }
    else
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

void mx_set_builstuct(t_builtin_command *my_command) {
    my_command->trig = false;
    my_command->exit_code = 0;
    my_command->unset_path = false;
    my_command->var = NULL;
    my_command->alias_list = NULL;
    my_command->path = (t_path_builtin *)malloc(sizeof(t_path_builtin));
    my_command->path->pwdP = getcwd(NULL, 0);
    my_command->path->pwdL = getcwd(NULL, 0);
    my_command->path->oldpwd = getcwd(NULL, 0);
    my_command->cd = (t_cd *)malloc(sizeof(t_cd));
    memset(my_command->cd, 0, sizeof(t_cd));
    my_command->pwd = (t_pwd *)malloc(sizeof(t_pwd));
    memset(my_command->pwd, 0, sizeof(t_pwd));
    my_command->echo = (t_echo *)malloc(sizeof(t_echo));
    memset(my_command->echo, 0, sizeof(t_echo));
    my_command->pid_ar = NULL;
    my_command->history = NULL;
    my_command->his = NULL;
    my_command->export_ar = NULL;
    my_command->file = fopen("/dev/tty", "w");
    build_export(&(my_command->export_ar));
}

int ush_loop(void) {
    unsigned char *line;
   int status = 0;
   t_queue **work = NULL;
   t_queue *p = NULL;


    int exit_code = 0;
    t_builtin_command my_command;

    mx_set_builstuct(&my_command);
    mx_mysetenv();
    while (my_command.trig == false) {
        line = mx_read_line(&my_command);
        if (line && line[0] != '\0' && !contral_d(&line, &my_command)) {
            work = mx_works_queue((char *)line);
            printf("WORKS QUEUE DONE - %s\n", work[0]->command);
            for (int i = 0; work[i]; i++) {
                p = work[i];
                for (; p; p = (*p).next) {
                    (*p).command = mx_expandParameter((*p).command, my_command.var, status);
                    printf("EXPAND DONE - %s\n", (*p).command);
                    (*p).command = mx_substitute((*p).command, &my_command);
                    printf("SUBSTITUTE DONE - %s\n", (*p).command);
                    status = mx_redirection((*p).command, &my_command);
                    printf("REDIRECTION DONE\n");
                    if (((*p).op == '&' && status == 1)
                        || ((*p).op == '|' && status == 0))
                            p = (*p).next;
                }
            }
        }
        exit_code = my_command.exit_code;
        del_work(&work);
        free(line);
        // system("leaks -q ush");
    }
    exit_func(&my_command);
    return exit_code;
}

void hdl(int sig) {
    sig = sig + 1 - 1;
}

int main(void) {
    int exit = 0;

    signal(SIGINT, hdl);
    signal(SIGTSTP, hdl);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    exit = ush_loop();
    system("leaks -q ush");
    return exit;
}


