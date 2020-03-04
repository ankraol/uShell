 #include "header.h"

 static t_history_name *creat_history(unsigned char *str, t_len_name *len) {
    t_history_name *history = (t_history_name *)malloc(sizeof(t_history_name));
    history->name = (unsigned char *)strdup((char *)str);
    history->n_len = len->n_len;
    history->n_byte = len->n_bute;
    history->previous = NULL;
    history->next = NULL;

    return history;
 }


void mx_push_back_history(t_history_name **history, unsigned char *str,
                          t_len_name *len) {
    t_history_name *front = creat_history(str, len);
    if ((*history) != NULL) {
        (*history) -> previous = front;
    }
    front->next = *history;
    *history = front;
}

void mx_delete_history(t_history_name **history) {
    t_history_name *tmp = NULL;

    while ((*history)) {
        tmp = (*history)->next;
        free((*history)->name);
        free((*history));
        *history = tmp;
    }
}
