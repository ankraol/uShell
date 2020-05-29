#include "header.h"

static int subExec(t_builtin_command *my_command, char *line) {
    int fd[2];
    t_queue **work = NULL;
    t_queue *p = NULL;
    int status = 0;

    pipe(fd);
    pid_t pid = fork();
    if (pid == 0) {
        close(1);
        dup(fd[1]);
        close(fd[1]);
        work = mx_works_queue(line);
        for (int i = 0; work[i]; i++) {
            p = work[i];
            for (; p; p = (*p).next) {
                (*p).command = mx_substitute((*p).command, my_command);
                status = mx_redirection((*p).command, my_command);
                if (((*p).op == '&' && status == 1)
                    || ((*p).op == '|' && status == 0))
                    {
                        p = (*p).next;
                    }
            }
        }
        exit(0);
        }
        else {
            close(fd[1]);
        }
        return fd[0];
}

char *mx_substitute(char *command, t_builtin_command *my_command) {
    t_inc index;
    char *mainCommand = (char *)malloc(sizeof(char) * strlen(command) * 50);
    char *line = NULL;

    memset(&index, 0, sizeof(t_inc));
    line = mx_subLine(&mainCommand, command, my_command, &index);

    // int fd[2];
    // t_queue **work = NULL;
    // t_queue *p = NULL;
    // int status = 0;
    if (index.a > 0) {
        // pipe(fd);
        // pid_t pid = fork();
        // if (pid == 0) {
        //     close(1);
        //     dup(fd[1]);
        //     close(fd[1]);
        //     work = mx_works_queue(line);
        //     for (int i = 0; work[i]; i++) {
        //         p = work[i];
        //         for (; p; p = (*p).next) {
        //             (*p).command = mx_substitute((*p).command, my_command);
        //             status = mx_redirection((*p).command, my_command);
        //             if (((*p).op == '&' && status == 1)
        //                 || ((*p).op == '|' && status == 0))
        //                 {
        //                     p = (*p).next;
        //                 }
        //         }
        //     }
        //     exit(0);
        // }
        // else {
        //     close(fd[1]);
        // }
        char c;
        int fd = subExec(my_command, line);
        // int i = k + 1;
        // index.b += 1
        for(; read(fd, &c, 1); index.b++) {
            if (c == '\n')
                c = ' ';
            // fprintf(stdout, "-%c-", c);
            mainCommand[index.b] = c;
        }
        close(fd);
        for (index.c += 1; command[index.c] != '\0' && command[index.c - 1] != '\0'; index.c++) {
            mainCommand[index.b] = command[index.c];
            fprintf(stdout, ". %c .", command[index.c]);
            index.b++;
        }
        if (mainCommand[index.b - 1] == ' ')
            mainCommand[index.b - 1] = '\0';
        else
            mainCommand[index.b] = '\0';
        mainCommand = realloc(mainCommand, strlen(mainCommand) + 1);
        return mainCommand;
    }
    return command;
}
