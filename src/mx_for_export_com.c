#include "header.h"

bool mx_find_in_export(char *str, t_export **export_list, char *change){
    t_export *buf = *export_list;
    while(buf) {
        if (strcmp(buf->name, str) == 0) {
            free(buf->value);
            buf->value = strdup(change);
            return true;
        }
        buf = buf->next;
    }
    return false;
}


static t_var *creat_var(char *name, char *val) {
    t_var *var_list = (t_var *)malloc(sizeof(t_var));

    var_list->name = strdup(name);
    var_list->meaning = strdup(val);
    var_list->next = NULL;

    return var_list;
 }


void mx_push_back_var(t_var **var_list, char *name, char *val) {
    t_var *front = creat_var(name, val);
    front->next = *var_list;
    *var_list = front;

}
