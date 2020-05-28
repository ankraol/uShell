#include "header.h"

// static bool iSsub(char *command) {
    // for (int i = 0; command[i] != '\0'; i++) {
        // if (command[i] == 96)
            // return true;
    // }
    // return false;
// }


static char *subLine(char **mainCommand, char *command, t_builtin_command *my_command, t_inc *index) {
    t_muteChar trig;
    char *line = (char *)malloc(sizeof(char) * strlen(command));

    memset(&trig, 0, sizeof(t_muteChar));
    
    for (; command[(*index).c] != '\0'; (*index).c++) {
        //printf("strat\n");
        //printf("%d\n", (*index).c);
        // fprintf(stdout, " -%c- ", command[(*index).c]);
        if (command[(*index).c] == 96 && command[(*index).c - 1] != 92 && trig.dQ == false) {
            if (trig.sQ == false) {
                trig.sQ = true;
            }
            else {
                break;
            }
        }
        else if (command[(*index).c - 1] == 36 && command[(*index).c] == 40 && trig.sQ == false) {
            if (trig.dQ == false) {
                trig.dQ = true;
            }
            else {
                trig.iSs = true;
                line[(*index).a] = command[(*index).c];
                (*index).a++;
            }
        }
        else if (command[(*index).c] == 41) {
            if (trig.iSs == true)
                trig.iSs = false;
            else
                break;
        }
        else if (trig.sQ == false && trig.dQ == false) {
            if (command[(*index).c] != 36) {
                (*mainCommand)[(*index).b] = command[(*index).c];
                (*index).b++;
            }
        }
        else if (trig.sQ == true || trig.dQ == true) {
                line[(*index).a] = command[(*index).c];
                (*index).a++;
        }
        //printf("%c\n", command[(*index).c]);
        //printf("%d\n", (*index).b);
    }
    //printf("endof cycle");
    line[(*index).a] = '\0';
    (*mainCommand)[(*index).b] = ' ';
    line = realloc(line, strlen(line) + 1);
    line = mx_aliasSearch(line, my_command->alias_list);
    //printf("command in stat func %s\n", *mainCommand);
    return line;
}

char *mx_substitute(char *command, t_builtin_command *my_command) {
    // bool ap = false;
    // bool iSbr = false;
    // bool extr = false;
    // char *line = (char *)malloc(sizeof(char) * strlen(command));
    t_inc index;
    char *mainCommand = (char *)malloc(sizeof(char) * strlen(command) * 50);
    char *line = NULL;
    // int j = 0;
    // int k = 0;
    // int i = 0;
    memset(&index, 0, sizeof(t_inc));
    //printf("in sub\n");
    line = subLine(&mainCommand, command, my_command, &index);
    // fprintf(stdout, "-%s-", mainCommand);
    //printf("MAIN COM = %s\n", mainCommand);
    //printf("after\n");
    // printf("main command - %s\n", mainCommand);
    // printf("im here");
    // fprintf(stdout, "command in CHECK FOR SUBSTITUTION %s\n", command);
    // for (; command[i] != '\0'; i++) {
    //     if (command[i] == 96 && command[i - 1] != 92 && iSbr == false) {
    //         if (ap == false) {
    //             ap = true;
    //         }
    //         else {
    //             // printf("I`M DONE WITH IT\n");
    //             break;
    //         }
    //     }
    //     else if (command[i - 1] == 36 && command[i] == 40 && ap == false) {
    //         if (iSbr == false)
    //             iSbr = true;
    //         else {
    //             extr = true;
    //             line[j] = command[i];
    //             j++;
    //         }
    //     }
    //     else if (command[i] == 41) {
    //         if (extr == true)
    //             extr = false;
    //         else {
    //             // printf("I`M DONE WITH IT\n");
    //             break;
    //         }
    //     }
    //     else if (ap == false && iSbr == false) {
    //         if (command[i] != 36) {
    //             mainCommand[k] = command[i];
    //             k++;
    //         }
    //     }
    //     else if (ap == true || iSbr == true) {
    //             line[j] = command[i];
    //             j++;
    //     }
    // }
    // // printf("count for line = %d count for maincommand = %d general count = %d\n", j, k, i);
    // line[j] = '\0';
    // mainCommand[k] = ' ';
    // line = realloc(line, strlen(line) + 1);
    // line = mx_aliasSearch(line, my_command->alias_list);
    // printf("line - %s\n", line);

    int fd[2];
    t_queue **work = NULL;
    t_queue *p = NULL;
    int status = 0;
    if (index.a > 0) {
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
        char c;
        // int i = k + 1;
        // index.b += 1
        for(; read(fd[0], &c, 1); index.b++) {
            if (c == '\n')
                c = ' ';
            // fprintf(stdout, "-%c-", c);
            mainCommand[index.b] = c;
        }
        close(fd[0]);
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
        //printf("MAIN command - %s\n", mainCommand);
        return mainCommand;
    }
    
    // mx_strdel(&mainCommand);
    // mx_strdel(&line);
    return command;
}
