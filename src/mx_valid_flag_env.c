#include "header.h"

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

void mx_valid_flag_env(char **arg, int ac, t_builtin_command *command) {
    extern char **environ;
    char **full_val = NULL;
    //char **new_env = NULL;
    t_env *env_list = NULL;
    char *path = NULL;
    int i = 0;


    bool flag_priority = false;
    bool flag_u = false;
    bool flag_p = false;
    bool i_access = true;
    bool be_command = false;
    bool find_program = false;

    if (ac == 1 && environ != NULL) {
        for (int i = 0; environ[i] != NULL; i++) {
            full_val = mx_strsplit(environ[i], '=');
            if (full_val[1])
                printf("%s=%s\n", full_val[0], full_val[1]);
            else
                printf("%s=\n", full_val[0]);
            mx_del_strarr(&full_val);
        }
    }
    else if (ac > 1) {
        printf("ac>1\n");
       build_env(&env_list);
        for (i = 1; i < ac; i++) {
            if (find_program)
                break;
            for (int j = 0; arg[i][j] != '\0'; j++) {
                printf("%d_______%d\n", flag_u, j);
                if (flag_u == true) {
                    if (i_access == true)
                        mx_variable_out(&(arg[i][j]), &env_list);
                    printf("/n--------\n");
                    printf("----%s-----%d\n", &(arg[i][j]), j);
                    flag_u = false;
                    flag_priority = false;
                    break;
                }
                if (flag_p == true) {
                    if (path != NULL && malloc_size(path))
                        free(path);
                    path = strdup(&(arg[i][j]));
                    flag_p = false;
                    flag_priority = false;
                    printf("Flag_p\n");
                    break;
                }

                if (flag_priority == true) {
                    if (arg[i][j] == 'u') {
                        flag_u = true;
                        printf("**********%d\n", j);
                    }
                    else if (arg[i][j] == 'P')
                        flag_p = true;
                    else if (arg[i][j] == 'i') {
                        if (i_access == true) {
                            mx_delete_env(&env_list);
                            i_access = false;
                        }
                    }
                    else if (arg[i][j] != '-') {
                        mx_delete_env(&env_list);
                        mx_printerr("env: illegal option -- ");
                        mx_printcharerr(arg[i][j]);
                        mx_printerr("\nusage: env [-i] [-P utilpath] [-u name]\
                                  [name=value ...] [utility [argument ...]]\n");
                        printf("error\n");
                        return;
                    }

                }
                if (j == 0 && arg[i][j] == '-' && flag_priority == false && be_command == false)
                    flag_priority = true;
                if (!flag_priority && arg[i][j] == '=') {
                    mx_push_back_env(&env_list, arg[i]);
                    be_command = true;
                    printf("BE_COMMAND--%d\n", j);
                    break;
                }
                if (!flag_priority && arg[i][j+1] == '\0') {
                    find_program = true;
                    printf("FIND_COMMAND--%d\n", j);
                    break;
                }
                if (arg[i][j+1] == '\0' && !flag_u && !flag_p && flag_priority) {
                    flag_priority = false;
                    printf("Flag_priority\n");
                 }
                }
            }
        if (!find_program)
            print_list(env_list);
        else { 
            printf("THIS is PROGRAM\n");
            if (path != NULL)
                printf("%s\n", path);
            mx_ush_execute_env(arg[i-1], command);
        }
            
        }

}

