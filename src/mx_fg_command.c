#include "header.h"


void mx_fg_command(t_builtin_command *command, char **arg, int ac) {
    t_builtin_command *buf = command;

    for(int i = 0; i < ac; i++) {
        printf("ARG == %s\n", arg[i]);
    }
    //printf("COMMAND == %s\n", command);
    buf = NULL;
}
    // t_pid_name *pid_buf = NULL;
    // int status_pid;
    // pid_t wpid;

// if (strcmp((char *)line, "fg") == 0) {
//             if (pid_ar != NULL) {
//                 kill (-(pid_ar->pid), SIGCONT);
//                 tcsetpgrp(1, pid_ar->pid);
//                 wpid = waitpid(pid_ar->pid, &status_pid, WUNTRACED);
//                 tcsetpgrp(1, getpid());

//                 if (WIFEXITED(status_pid)) {
//                     pid_buf = pid_ar->next;
//                     free(pid_ar);
//                     pid_ar = pid_buf;
//                     mx_printstr("exit");
//                     sleep(2);
//                 }
//                 else if (WIFSTOPPED(status_pid)) {

//                 }

//                 else if (WTERMSIG(status_pid)) { //ctrl+C
//                      mx_printstr("and now term");
//                      sleep(2);
//                     pid_buf = pid_ar->next;
//                     free(pid_ar);
//                     pid_ar = pid_buf;
                    
//                 }
//              }
//         }
