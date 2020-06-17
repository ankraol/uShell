#include "header.h"

static void print_list(t_env *export_list) {
 
    while (export_list) {
        mx_printstr(export_list->name);
        mx_printchar('\n');

        export_list = export_list->next;
    }
}

static char **create_env_arr(t_env *export_list) {
    t_env *buf = export_list;
    int i = 0;
    char **arr = NULL;

    if (export_list == NULL)
        return NULL;
    while(buf) {
        i++;
        buf = buf->next;
    }
    arr = (char **)malloc(sizeof(char *) * (i+1));
    i = 0;
    while (export_list) {
        arr[i] = strdup(export_list->name);
        i++;
        export_list = export_list->next;
    }
    arr[i] = NULL;
    return arr;
}

static char *build_prog(int index, char **arr) {
    char *prog  = NULL;

    if (arr[index+1] != NULL) {
        for (int i = index; arr[i] != NULL; i++) {
            if (prog != NULL)
                prog = mx_strjoin_two(prog, " ");
            prog = mx_strjoin_two(prog, arr[i]);
        }
    }
    else
        prog = strdup(arr[index]);
    return prog;
}

int mx_execute_command(t_builtin_command *command, t_env **env_list, 
                        t_env_flag *env_flag, char **program) {
    char **new_env = NULL;
    char *prog = NULL;
    int ret = 0;

    if (!(env_flag->find_program))
        print_list(*env_list);
    else {
        new_env = create_env_arr(*env_list);
        command->execute = false;
        prog = build_prog(env_flag->index, program);
        ret = mx_ush_execute_env(prog, command, new_env, env_flag->pa);
    }
    mx_delete_env(env_list);
    mx_strdel(&(env_flag->pa));
    free(env_flag);
    mx_del_strarr(&new_env);
    mx_strdel(&prog);
    return ret;
}
