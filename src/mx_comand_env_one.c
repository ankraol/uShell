#include "header.h"

static void build_env(t_env **env_list) {
    extern char **environ;

    if (environ != NULL) {
        for (int i = 0; environ[i] != NULL; i++) {
            mx_push_back_env(env_list, environ[i]);
        }
    }
}

t_env_flag *mx_creat_flag() {
    t_env_flag *flag = (t_env_flag *)malloc(sizeof(t_env_flag));

    flag->flag_priority = false;
    flag->flag_u = false;
    flag->flag_p = false;
    flag->i_access = true;
    flag->be_command = false;
    flag->find_program = false;
    flag->pa = NULL;
    flag->index = 0;
    return flag;
}

static void fail(t_env_flag *env_flag, t_env **env_list, char var, int *err) {
    mx_delete_env(env_list);
    free(env_flag->pa);
    free(env_flag);
    mx_printerr("env: illegal option -- ");
    mx_printcharerr(var);
    mx_printerr("\nusage: env [-i] [-P utilpath] [-u name] \n\
            [name=value ...] [utility [argument ...]]\n");
    *err = 1;

}

static bool flag_priority(t_env_flag *env_flag, t_env **env, char var,
                            int *err) {
    if (var == 'u') {
        env_flag->flag_u = true;
        return true;
    }
    else if (var == 'P') {
        env_flag->flag_p = true;
        return true;
    }
    else if (var == 'i') {
        if (env_flag->i_access == true) {
            mx_delete_env(env);
            env_flag->i_access = false;
            return true;
        }
    }
    else if (var != '-') {
        fail(env_flag, env, var, err);
        return false;
    }
    return true;
}

void mx_env_two(char **arg, int ac, t_builtin_command *command, int *err) {
    t_env *env_list = NULL;
    int i = 0;
    t_env_flag *env_flag = mx_creat_flag();

    build_env(&env_list);
    for (i = 1; i < ac; i++) {
        if (env_flag->find_program)
            break;
        for (int j = 0; arg[i][j] != '\0'; j++) {
            if (mx_glag_p_u(&env_list, env_flag, &(env_flag->pa),&(arg[i][j])))
                break;
            if (env_flag->flag_priority == true)
                if (!flag_priority(env_flag, &env_list, arg[i][j], err))
                    return;
            if (mx_flag_command(arg[i], j, env_flag, &env_list))
                break;
        }
    }
    env_flag->index = i - 1;
    *err = mx_execute_command(command, &env_list, env_flag, arg);
}
