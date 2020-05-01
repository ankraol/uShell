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


static bool path_check(char **path, char *command, char ***argv) {
    if (*path == NULL) {
        mistake(command, argv, path);
        return true;
    }
    return false;
}

int mx_ush_execute_env(char *command, t_builtin_command *my_command,
                       char **new_env, char *path_env, t_path_builtin *pwd) {
    pid_t pid;
    printf("Comnad %s Comand \n", command);
    char **argv = mx_tokenSplit(command);
    int val_ret = 0;
    char *path = mx_read_env(argv[0], path_env, my_command);
    bool builtin = false;

    if (my_command->execute == true)
        builtin = mx_valid_command(argv, mx_count_elem(argv), pwd, my_command);
    if (!builtin) {
        if (path_check(&path, command, &argv))
            return 1;
        pid = fork();
        if (pid == 0) {
            mx_set_signal();
            if (my_command->execute == false) {
                // set_env(new_env);
                // if (mx_valid_command(argv, mx_count_elem(argv), pwd, my_command))
                //     exit(0);
                if (execve(path, argv, new_env) == -1) {
                    mistake(command, &argv, &path);
                    return 1;
                }
            }
            if (my_command->execute == true) {
                if (execvp(path, argv) == -1) {
                    mistake(command, &argv, &path);
                    return 1;
                }
            }

        }
        else
            parent(pid, &val_ret, my_command, argv);
    }
    tcsetpgrp(1, getpid());
    del_all(&argv, &path);
    return val_ret;
}
