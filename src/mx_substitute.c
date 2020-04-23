#include "header.h"

// static bool iSsub(char *command) {
    // for (int i = 0; command[i] != '\0'; i++) {
        // if (command[i] == 96)
            // return true;
    // }
    // return false;
// }

char *mx_substitute(char *command, t_path_builtin *pwd, t_builtin_command *my_command) {
    bool ap = false;
    bool iSbr = false;
    bool extr = false;

    char *line = (char *)malloc(sizeof(char) * strlen(command));
    char *mainCommand = (char *)malloc(sizeof(char) * strlen(command) * 50);
    int j = 0;
    int k = 0;
    int i = 0;

    // fprintf(stdout, "command in CHECK FOR SUBSTITUTION %s\n", command);
    for (; command[i] != '\0'; i++) {
        if (command[i] == 96 && command[i - 1] != 92 && iSbr == false) {
            if (ap == false) {
                ap = true;
            }
            else {
                // printf("I`M DONE WITH IT\n");
                break;
            }
        }
        else if (command[i - 1] == 36 && command[i] == 40 && ap == false) {
            if (iSbr == false)
                iSbr = true;
            else {
                extr = true;
                line[j] = command[i];
                j++;
            }
        }
        else if (command[i] == 41) {
            if (extr == true)
                extr = false;
            else {
                // printf("I`M DONE WITH IT\n");
                break;
            }
        }
        else if (ap == false && iSbr == false) {
            if (command[i] != 36) {
                mainCommand[k] = command[i];
                k++;
            }
        }
        else if (ap == true || iSbr == true) {
                line[j] = command[i];
                j++;
        }
    }
    // printf("count for line = %d count for maincommand = %d general count = %d\n", j, k, i);
    line[j] = '\0';
    mainCommand[k] = ' ';
    line = realloc(line, strlen(line) + 1);
    line = mx_aliasSearch(line, my_command->alias_list);
    // printf("line - %s\n", line);

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
                    (*p).command = mx_substitute((*p).command, pwd, my_command);
                    status = mx_redirection((*p).command, pwd, my_command);
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
        // int i = k + 1;
        for(k += 1; read(fd[0], &c, 1); k++) {
            if (c == '\n')
                c = ' ';
            mainCommand[k] = c;
        }
        close(fd[0]);
        for (i += 1; command[i] != '\0'; i++) {
            mainCommand[k] = command[i];
            k++;
        }
        mainCommand[k] = '\0';
        mainCommand = realloc(mainCommand, strlen(mainCommand) + 1);
        // printf("command - %s\n", mainCommand);
        return mainCommand;
    }
    mx_strdel(&mainCommand);
    mx_strdel(&line);
    return command;
}
