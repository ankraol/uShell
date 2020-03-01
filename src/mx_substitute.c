#include "header.h"

char *mx_substitute(char *command) {
    bool ap = false;
    char *line = (char *)malloc(sizeof(char) * strlen(command));
    char *mainCommand = (char *)malloc(sizeof(char) * strlen(command));
    int j = 0;
    int k = 0;

    for (int i = 0; command[i] != '\0'; i++) {
        if (command[i] == 96 && command[i -1] != 92) {
            if (ap == false) {
                ap = true;
            }
            else {
                ap = false;
            }
        }
        if (ap == false) {
            if (command[i] != 96 && command[i] != ' ') {
                mainCommand[k] = command[i];
                k++;
            }
        }
        else if (ap == true) {
            if (command[i] != 96) {
                line[j] = command[i];
                j++;
            }
        }
    }
    line[j] = '\0';
    mainCommand[k] = ' ';
    line = realloc(line, strlen(line) + 1);
    printf("substitution -> %s\n", line);

    int fd[2];
    t_queue **work = NULL;
    t_queue *p = NULL;
    int status = 0;
    if (j > 0) {
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
                    status = mx_redirection((*p).command);
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
        char c;
        int i = k + 1;
        for(; read(fd[0], &c, 1); i++) {
            if (c == '\n')
                c = ' ';
            mainCommand[i] = c;
        }
        close(fd[0]);
        mainCommand[i] = '\0';
        mainCommand = realloc(mainCommand, strlen(mainCommand) + 1);
        printf("command -> %s\n", mainCommand);
        return mainCommand;
    }
    return command;
}
