 #include "header.h"

 static t_pid_name *creat_pid(int pid, char *name, int num) {
    t_pid_name *pid_list = (t_pid_name *)malloc(sizeof(t_pid_name));

    pid_list->pid = pid;
    pid_list->name = strdup(name);
    pid_list->number = num;
    pid_list->next = NULL; 

    return pid_list;
 }


void mx_push_back_pid(t_pid_name **pid_list, int pid, char *name, int num) {
    t_pid_name *front = creat_pid(pid, name, num);
    front->next = *pid_list;
    *pid_list = front;
    mx_printstr("\n");
}

int mx_get_pid_num(t_pid_name **pid_list) {
    t_pid_name *buf = *pid_list;

    if ((*pid_list) == NULL) {
        return 1;
    }
    else {
        return (buf->number) + 1;
    }
}

void mx_delete_pid(t_pid_name **pid_list) {
    t_pid_name *tmp = NULL;

    while ((*pid_list)) {
        tmp = (*pid_list)->next;
        free((*pid_list)->name);
        free((*pid_list));
        *pid_list = tmp;
    }
}
