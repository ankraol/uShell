#include "header.h"

static void flag_u(t_env_flag *env_flag, t_env **env_list, char *var) {
    if (env_flag->i_access == true)
        mx_variable_out(var, env_list);
    env_flag->flag_u = false;
    env_flag->flag_priority = false;
}

static void flag_p(char **path, t_env_flag *env_flag, char *var) {
    if (*path != NULL && malloc_size(*path))
        free(*path);
    *path = strdup(var);
    env_flag->flag_p = false;
    env_flag->flag_priority = false;
}

bool mx_glag_p_u(t_env **env_list, t_env_flag *env_flag, char **path, 
                char *var) {
    if (env_flag->flag_u == true) {
        flag_u(env_flag, env_list, var);
        return true;
    }
    if (env_flag->flag_p == true) {
        flag_p(path, env_flag, var);
        return true;
    }
    return false;
}

void mx_env_one() {
    extern char **environ;
    char **full_val = NULL;

    if (environ != NULL) {
        for (int i = 0; environ[i] != NULL; i++) {
            full_val = mx_strsplit(environ[i], '=');
            if (full_val[1])
                printf("%s=%s\n", full_val[0], full_val[1]);
            else
                printf("%s=\n", full_val[0]);
            mx_del_strarr(&full_val);
        }
    }
}
