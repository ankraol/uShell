#include "header.h"


static void print_list(t_env *export_list) {
 
    while (export_list) {
        printf("%s\n", export_list->name);
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
