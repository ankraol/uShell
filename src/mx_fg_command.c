#include "header.h"

int mx_get_peid(int n, t_pid_name *pid_arr) {
    t_pid_name *pid_buf = pid_arr;
    
    while(pid_buf) {
        if (n == pid_buf->number)
            return pid_buf->pid;
        pid_buf = pid_buf->next;
    }
    return 0;
}

int mx_get_peid_name(char *name, t_pid_name *pid_arr) {
    t_pid_name *pid_buf = pid_arr;
    
    while(pid_buf) {
        if (strcmp(name, pid_buf->name) == 0)
            return pid_buf->pid;
        pid_buf = pid_buf->next;
    }
    return 0;
}

 void mx_wait_cont(t_pid_name **pid_ar, int n_pid) {
    t_pid_name *pid_buf = NULL;;
    int status_pid;
    pid_t wpid;

    kill (-(n_pid), SIGCONT);
    tcsetpgrp(1, n_pid);
    wpid = waitpid(n_pid, &status_pid, WUNTRACED);
    tcsetpgrp(1, getpid());
    if (WIFEXITED(status_pid)) {
        pid_buf = (*pid_ar)->next;
        free((*pid_ar)->name);
        free((*pid_ar));
        (*pid_ar) = pid_buf;
    }
    else if (WTERMSIG(status_pid) && !(WIFSTOPPED(status_pid))) {
        free((*pid_ar)->name);
        pid_buf = (*pid_ar)->next;
        free((*pid_ar));
        (*pid_ar) = pid_buf;
    }
}


void mx_fg_command(t_builtin_command *command, char **arg, int ac) {

    if (ac == 1) {
        if (command->pid_ar != NULL)
            mx_wait_cont(&(command)->pid_ar, command->pid_ar->pid);
        else 
            mx_printerr("fg: no current job\n");
    }
    else {
        mx_for_fg_command(command, arg, ac);
    }
}
