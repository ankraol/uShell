#include "header.h"

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

static void buildPath(t_builtin_command **my_command) {
    (*my_command)->path = (t_path_builtin *)malloc(sizeof(t_path_builtin));
    (*my_command)->path->pwdP = getcwd(NULL, 0);
    (*my_command)->path->pwdL = getcwd(NULL, 0);
    (*my_command)->path->oldpwd = getcwd(NULL, 0);
}

void mx_set_builstuct(t_builtin_command *my_command) {
    my_command->trig = false;
    my_command->exit_code = 0;
    my_command->unset_path = false;
    my_command->var = NULL;
    my_command->alias_list = NULL;
    buildPath(&(my_command));
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
    (isatty(0)) ? (my_command->is_inp = true) : (my_command->is_inp = false);
    my_command->is_comand = false;
}
