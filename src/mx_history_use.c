 #include "header.h"

 t_history_name *mx_creat_history(unsigned char *str, int byte, int len) {
    t_history_name *history = (t_history_name *)malloc(sizeof(t_history_name));
    history->name = str;
    history->n_len = len;
    history->n_byte = byte;
    history->previous = NULL;
    history->next = NULL;

    return history;
 }


void mx_push_back_history(t_history_name **history, unsigned char *str,
                          int n_byte, int len) {
    t_history_name *front = mx_creat_history(str, n_byte, len);
    if ((*history) != NULL) {
        (*history) -> previous = front;
    }
    front->next = *history;
    *history = front;
}

void mx_delete_history(t_history_name **history) {
    
}
