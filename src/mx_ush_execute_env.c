#include "header.h"


void mx_del_all(char ***argv, char **path) {
    if (*argv != NULL)
        mx_del_strarr(argv);
    if (*path != NULL)
        mx_strdel(path);
}




void mx_mistake(char *command, char ***argv, char **path, bool flag) {
    if (flag) {
        mx_printerr("ush: ");
        mx_printerr("command not found: ");
        mx_printerr(command);
        mx_printerr("\n");
    }
    else{
        mx_printerr("env: ");
        mx_printerr(command);
        mx_printerr(": No such file or directory\n");
    }
    mx_del_all(argv, path);
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
    else if (WTERMSIG(status)) {//ctrl+C
        *val_ret = 130;
        mx_printstr("\n");
    }
    else if (status != 0)
        *val_ret = 1;
}

// static void set_env(char **new_env) {
//     extern char **environ;
//     char **full_val = NULL;

//     if (environ != NULL) {
//         for (int i = 0; environ[i] != NULL; i++) {
//             full_val = mx_strsplit(environ[i], '=');
//             if (full_val[0] != NULL)
//                 unsetenv(full_val[0]);
//             mx_del_strarr(&full_val);
//         }
//     }
//     if (new_env != NULL) {
//         for (int i = 0; new_env[i] != NULL; i++) {
//             full_val = mx_strsplit(new_env[i], '=');
//             if (full_val[0] != NULL)
//                 setenv(full_val[0], full_val[1], 1);
//             mx_del_strarr(&full_val);
//         }
//     }
// }


static bool path_check(char **path, char *command, char ***argv, bool flag) {
    if (*path == NULL) {
        mx_mistake(command, argv, path, flag);
        return true;
    }
    return false;
}
void last_func(char ***argv, char **str) {
    tcsetpgrp(1, getpid());
    mx_del_all(argv, str);
}

int mx_ush_execute_env(char *com, t_builtin_command *my_com,
                       char **new_env, char *path_env) {
    pid_t pid;
    char **argv = mx_tokenSplit(com);
    int val_ret = 1;

    my_com->path_for_ex = mx_read_env(argv[0], path_env, my_com);
    if (my_com->execute == true)
        val_ret = mx_valid_command(argv, mx_count_elem(argv), my_com);
    if (val_ret != 0) {
        if (path_check(&(my_com->path_for_ex), com, &argv, my_com->execute))
            return 1;
        pid = fork();
        if (pid == 0) {
            if (mx_child(com, my_com, new_env, &argv) == 1)
                return 1;
        }
        else
            parent(pid, &val_ret, my_com, argv);
    }
    last_func(&argv, &(my_com->path_for_ex));
    return val_ret;
}
