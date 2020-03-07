 #include "header.h"

 static t_pid_name *creat_pid(int pid) {
    t_pid_name *pid_list = (t_pid_name *)malloc(sizeof(t_pid_name));
    pid_list->pid = pid;
    pid_list->next = NULL;

    return pid_list;
 }


void mx_push_back_pid(t_pid_name **pid_list, int pid) {
    t_pid_name *front = creat_pid(pid);
    front->next = *pid_list;
    *pid_list = front;
    // fprintf(stdout, "--%d--\n", (*pid_list)->pid);
    // fflush(stdout);
}

void mx_delete_pid(t_pid_name **pid_list) {
    t_pid_name *tmp = NULL;

    while ((*pid_list)) {
        tmp = (*pid_list)->next;
        free((*pid_list));
        *pid_list = tmp;
    }
}
