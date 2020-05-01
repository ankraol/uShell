#include "header.h"

static bool be_find_comad(char *var, int j, t_env_flag *env_flag, 
                        t_env **env_list) {
    if (!(env_flag->flag_priority) && var[j] == '=') {
        mx_push_back_env(env_list, var);
        env_flag->be_command = true;
        printf("BE_COMMAND--%d\n", j);
        return true;
    }
    if (!(env_flag->flag_priority) && var[j+1] == '\0') {
        env_flag->find_program = true;
        printf("FIND_COMMAND--%d\n", j);
        return true;
    }
    if (var[j+1] == '\0' && !(env_flag->flag_u)
        && !(env_flag->flag_p) && env_flag->flag_priority) {
            env_flag->flag_priority = false;
            printf("Flag_priority\n");
            return false;
    }
    return false;
}

static void flag_prior( t_env_flag *env_flag, char *var, int j) {
    if (j == 0 && var[j] == '-' && env_flag->flag_priority == false 
        && env_flag->be_command == false) {
        env_flag->flag_priority = true;
    }
}


bool mx_flag_command(char *var, int j, t_env_flag *env_flag, 
                    t_env **env_list) {
    flag_prior(env_flag, var, j);
    if (be_find_comad(var, j, env_flag, env_list))
        return true;
    return false;
}
