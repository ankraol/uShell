#include "header.h"

static t_env *creat_env(char *name) {
    t_env *env_list = (t_env *)malloc(sizeof(t_env));

    env_list->name = strdup(name);
    env_list->next = NULL;

    return env_list;
 }


void mx_push_back_env(t_env **pid_env, char *name) {
    t_env *front = creat_env(name);
    t_env *buf = *pid_env;

    if (buf == NULL) {
        *pid_env = front;
        return;
    }
    while(buf->next != NULL)
        buf = buf->next;

    buf->next = front;

}


void mx_delete_env(t_env **env_list) {
    t_env *tmp = NULL;

    while ((*env_list)) {
        tmp = (*env_list)->next;
        free((*env_list)->name);
        free((*env_list));
        *env_list = tmp;
    }
}


