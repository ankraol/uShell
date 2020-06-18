#include "header.h"

static void exit_code(int status, int *val_ret) {
    *val_ret = WEXITSTATUS(status);
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
        exit_code(status, val_ret);
    else if (WIFSTOPPED(status)) {//ctrl+Z
        number = mx_get_pid_num(&my_command->pid_ar);
        mx_push_back_pid(&my_command->pid_ar, wpid, argv[0], number);
        *val_ret = 146;
    }
    else if (WTERMSIG(status)) {//ctrl+C
        *val_ret = 130;
        mx_printstr("\n");
    }
}


static bool isUpper(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < 65 || str[i] > 97)
            return false;
    }
    return true;
}

static bool path_check(char **path, char ***argv, t_builtin_command *my_com) {
    if (my_com->is_comand) {
        mx_del_all(argv, path);
        return true;
    }
    else if (*path == NULL) {
        mx_mistake(*argv[0], argv, path, my_com->execute);
        return true;
    }
    return false;
}

static void lowwerCase(char **str) {
    char *newLine = (char *)malloc(sizeof(char) * (strlen(str[0]) + 1));
    int i = 0;

    for (; str[0][i] != '\0'; i++) {
        newLine[i] = str[0][i] + 32;
    }
    newLine[i] = '\0';
    mx_strdel(&str[0]);
    str[0] = newLine;
}

void last_func(char ***argv, char **str) {
    tcsetpgrp(1, getpid());
    mx_del_all(argv, str);
}

int mx_ush_execute_env(char *com, t_builtin_command *my_com,
                       char **new_env, char *path_env) {
    pid_t pid;
    char **argv = mx_tokenSplit(com);
    int val_ret = 999;
    my_com->is_comand = false;
    
    if (my_com->execute == true) {
        if (isUpper(argv[0]))
            lowwerCase(argv);
        val_ret = mx_valid_command(argv, mx_count_elem(argv), my_com);
    }
    if (val_ret == 999) {
        my_com->path_for_ex = mx_read_env(argv[0], path_env, my_com);
        val_ret = 0;
        if (path_check(&(my_com->path_for_ex), &argv, my_com))
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
