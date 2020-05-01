#include "header.h"


static void del_all(char ***argv, char **path) {
    if (*argv != NULL)
        mx_del_strarr(argv);
    if (*path != NULL)
        mx_strdel(path);
}

static void mistake(char *command, char ***argv, char **path) {
    mx_printerr("env: ");
    mx_printerr(command);
    mx_printerr(": No such file or directory\n");
    del_all(argv, path);
}

static void parent(pid_t pid, int *val_ret, t_builtin_command *my_command,
                    char **argv) {
    int number = 0;
    pid_t wpid;
    int status = 0;

    setpgid(pid, pid);
    tcsetpgrp(1, pid);
    wpid = waitpid(pid, &status, WUNTRACED);
    if (WIFEXITED(status))
        *val_ret = 0;
    else if (WIFSTOPPED(status)) {//ctrl+Z
        number = mx_get_pid_num(&my_command->pid_ar);
        mx_push_back_pid(&my_command->pid_ar, wpid, argv[0], number);
        *val_ret = 146;
    }
    else if (WTERMSIG(status)) //ctrl+C
        *val_ret = 130;
    else if (status != 0)
        *val_ret = 1;
}


static bool path_check(char **path, char *command, char ***argv) {
    if (*path == NULL) {
        mistake(command, argv, path);
        return true;
    }
    return false;
}

int mx_ush_execute_env(char *command, t_builtin_command *my_command,
                       char **new_env, char *path_env) {
    pid_t pid;
    char **argv = mx_tokenSplit(command);
    int val_ret = 0;
    char *path = mx_read_env(argv[0], path_env, my_command);

    if (path_check(&path, command, &argv))
        return 1;
    pid = fork();
    if (pid == 0) {
        mx_set_signal();
        if (execve(path, argv, new_env) == -1) {
            mistake(command, &argv, &path);
            return 1;
        }
    }
    else
        parent(pid, &val_ret, my_command, argv);
    tcsetpgrp(1, getpid());
    del_all(&argv, &path);
    return val_ret;
}
