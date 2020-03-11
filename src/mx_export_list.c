 #include "header.h"

 static t_export *creat_export(char *name, char *val) {
    t_export *export_list = (t_export *)malloc(sizeof(t_export));

    export_list->name = mx_strdup(name);
    if (val != NULL)
        export_list->value = mx_strdup(val);
    else 
        export_list->value = mx_strnew(1);
    export_list->next = NULL;

    return export_list;
 }


void mx_push_back_export(t_export **export_list, char *name, char *val) {
    t_export *front = creat_export(name, val);
    front->next = *export_list;
    *export_list = front;

}


void mx_delete_export(t_export **export_list) {
    t_export *tmp = NULL;

    while ((*export_list)) {
        tmp = (*export_list)->next;
        free((*export_list)->name);
        free((*export_list)->value);
        free((*export_list));
        *export_list = tmp;
    }
}
