#include "header.h"

static void delete(char **name, char **val, t_export **list) {
    free(*name);
    free(*val);
    free((*list));
}

static void variable_out(char *command, t_export **list) {
    t_export *buf = *list;
    t_export *temp = NULL;

    if (buf != NULL) {
        if (strcmp(command, (*list)->name) == 0) {
            temp = (*list)->next;
            delete(&((*list)->value), &((*list)->name), list);
            (*list) = temp;
            return;
        }
        while (buf->next) {
            if (strcmp(command, buf->next->name) == 0) {
                temp = buf->next->next;
                delete(&(buf->next->value), &(buf->next->name), &(buf->next));
                buf->next = temp;
                return;
            }
            buf = buf->next;
        }
    }
}


void mx_unset_command(t_builtin_command *command, int ac, char **arg) {
    if (ac == 1)
        mx_printerr("unset: not enough arguments\n");

    else {
        for (int i = 1; i < ac; i++) {
            variable_out(arg[i], &command->export_ar);
            if (getenv(arg[i]) != 0)
                unsetenv(arg[i]);
        }
        
    }
}
