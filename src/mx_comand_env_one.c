#include "header.h"

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

static void print_list(t_env *export_list) {
 
    while (export_list) {
        printf("%s\n", export_list->name);
        export_list = export_list->next;
    }
}


static void build_env(t_env **env_list) {
    extern char **environ;

    if (environ != NULL) {
        for (int i = 0; environ[i] != NULL; i++) {
            mx_push_back_env(env_list, environ[i]);
        }
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

t_env_flag *mx_creat_flag() {
    t_env_flag *flag = (t_env_flag *)malloc(sizeof(t_env_flag));

    flag->flag_priority = false;
    flag->flag_u = false;
    flag->flag_p = false;
    flag->i_access = true;
    flag->be_command = false;
    flag->find_program = false;
    flag->pa = NULL;
    return flag;
}

void mx_flag_u(t_env_flag *env_flag, t_env **env_list, char *var) {
    if (env_flag->i_access == true)
        mx_variable_out(var, env_list);
    env_flag->flag_u = false;
    env_flag->flag_priority = false;
}

void mx_flag_p(char **path, t_env_flag *env_flag, char *var) {
    if (*path != NULL && malloc_size(*path))
        free(*path);
    *path = strdup(var);
    env_flag->flag_p = false;
    env_flag->flag_priority = false;
}

static void fail(t_env_flag *env_flag, t_env **env_list, char var) {
    mx_delete_env(env_list);
    free(env_flag->pa);
    free(env_flag);
    mx_printerr("env: illegal option -- ");
    mx_printcharerr(var);
    mx_printerr("\nusage: env [-i] [-P utilpath] [-u name] \
                [name=value ...] [utility [argument ...]]\n");
    printf("error\n");
}

bool mx_flag_priority(t_env_flag *env_flag, t_env **env_list, char var) {
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
            mx_delete_env(env_list);
            env_flag->i_access = false;
            return true;
        }
    }
    else if (var != '-') {
        fail(env_flag, env_list, var);
        return false;
    }
    return true;
}

bool mx_be_find_comad(char *var, int j, t_env_flag *env_flag, 
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

void mx_execute_command(t_builtin_command *command, t_env **env_list, 
                        t_env_flag *env_flag, char *program) {
    char **new_env = NULL;
    
    if (!(env_flag->find_program))
        print_list(*env_list);
    else {
        printf("befor_arr\n");
        new_env = create_env_arr(*env_list);
        if (new_env == NULL)
            printf("NULL");
        // for (int v= 0; new_env[v] != NULL; v++)
        //     printf("**%s**\n", new_env[v]);
        printf("THIS is PROGRAM - %s\n", program);
        if (env_flag->pa != NULL)
            printf("%s\n", env_flag->pa );
        mx_ush_execute_env(program, command, new_env, env_flag->pa );
    }
    mx_delete_env(env_list);
    if (env_flag->pa != NULL)
        free(env_flag->pa);
    free(env_flag);
    if (new_env != NULL)
        mx_del_strarr(&new_env);
}

bool mx_glag_p_u(t_env **env_list, t_env_flag *env_flag, char **path, 
                char *var) {
    if (env_flag->flag_u == true) {
        mx_flag_u(env_flag, env_list, var);
        return true;
    }
    if (env_flag->flag_p == true) {
        mx_flag_p(path, env_flag, var);
        return true;
    }
    return false;
}

void mx_flag_prior( t_env_flag *env_flag, char *var, int j) {
    if (j == 0 && var[j] == '-' && env_flag->flag_priority == false 
        && env_flag->be_command == false) {
        env_flag->flag_priority = true;
    }
}

bool mx_flag_command(char *var, int j, t_env_flag *env_flag, 
                    t_env **env_list) {
    mx_flag_prior(env_flag, var, j);
    if (mx_be_find_comad(var, j, env_flag, env_list))
        return true;
    return false;
}
void mx_env_two(char **arg, int ac, t_builtin_command *command) {
    t_env *env_list = NULL;
    int i = 0;
    t_env_flag *env_flag = mx_creat_flag();

    build_env(&env_list);
    for (i = 1; i < ac; i++) {
        if (env_flag->find_program)
            break;
        for (int j = 0; arg[i][j] != '\0'; j++) {
            if (mx_glag_p_u(&env_list, env_flag, &(env_flag->pa), &(arg[i][j])))
                break;
            if (env_flag->flag_priority == true)
                if (!mx_flag_priority(env_flag, &env_list, arg[i][j]))
                    return;
            if (mx_flag_command(arg[i], j, env_flag, &env_list))
                break;
        }
    }
    mx_execute_command(command, &env_list, env_flag, arg[i-1]);
}
