#include "header.h"

static bool check_list(char *str, char *name) {
    char **buf_arr = mx_strsplit(name, '=');

    if (strcmp(str, buf_arr[0]) == 0) {
        mx_del_strarr(&buf_arr);
        return true;
    }
    mx_del_strarr(&buf_arr);
    return false;
}

static void delete(char **name, t_env **list) {
    free(*name);
    free((*list));
}

void mx_variable_out(char *command, t_env **list) {
    t_env *buf = *list;
    t_env *temp = NULL;

    if (buf != NULL) {
        if (check_list(command, (*list)->name)) {
            temp = (*list)->next;
            delete(&((*list)->name), list);
            (*list) = temp;
            return;
        }
        while (buf->next) {
            if (check_list(command, buf->next->name)) {
                temp = buf->next->next;
                delete(&(buf->next->name), &(buf->next));
                buf->next = temp;
                return;
            }
            buf = buf->next;
        }
    }
}
