#include "header.h"

static void del_work( t_queue ***work) {
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

static void execLoop(char *line, int *status, t_builtin_command *my_command) {
    t_queue **work = mx_works_queue(line);
    t_queue *p = NULL;

    if (work) {
        for (int i = 0; work[i]; i++) {
            p = work[i];
            for (; p; p = (*p).next) {
                (*p).command = mx_expandParameter((*p).command, my_command->var,
                                                    (*status));
                (*p).command = mx_substitute((*p).command, my_command);
                (*status)= mx_redirection((*p).command, my_command);
                if (((*p).op == '&' && (*status) == 1)
                    || ((*p).op == '|' && (*status) == 0))
                    {
                        p = (*p).next;
                    }
            }
        }
        del_work(&work);
    }
}

static bool contral_d(unsigned char **str, t_builtin_command *my_command) {
    if (*str[0] == 4) {
        if (my_command->pid_ar != NULL) {
            mx_printerr("ush: you have suspended jobs.\n");
            mx_strdel((char **) str);
            my_command->trig = false;
            return true;
        }
        else {
            my_command->trig = true;
            mx_strdel((char **) str);
            return true;
        }
    }
    return false;
}

static void mysetenv() {
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

int mx_ush_loop(void) {
    unsigned char *line;
    int status = 0;
    int exit_code = 0;
    t_builtin_command my_command;

    mx_set_builstuct(&my_command);
    mysetenv();
    while (my_command.trig == false) {
        line = mx_read_line(&my_command);
        if (line && line[0] != '\0' && !contral_d(&line, &my_command)) {
            if (mx_checkLine((char *)line))
                execLoop((char *)line, &status, &my_command);
            exit_code = my_command.exit_code;
            free(line);
        }
    }
    mx_exit_func(&my_command);
    return exit_code;
}
