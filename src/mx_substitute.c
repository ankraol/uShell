#include "header.h"

static void subFill(int fd, t_inc index, char **mainCommand, char *command) {
    char c;

    for(; read(fd, &c, 1); index.b++) {
        if (c == '\n')
            c = ' ';
        (*mainCommand)[index.b] = c;
    }
    close(fd);
    for (index.c += 2; command[index.c] != '\0' && command[index.c - 1] != '\0'; index.c++) {
        (*mainCommand)[index.b] = command[index.c];
        index.b++;
    }
    if ((*mainCommand)[index.b - 1] == ' ')
        (*mainCommand)[index.b - 1] = '\0';
    else
        (*mainCommand)[index.b] = '\0';
    (*mainCommand) = realloc(*mainCommand, strlen(*mainCommand) + 1);
}

char *mx_substitute(char *command, t_builtin_command *my_command) {
    int fd;
    t_inc index;
    char *mainCommand = (char *)malloc(sizeof(char) * strlen(command) * 50);
    char *line = NULL;

    memset(&index, 0, sizeof(t_inc));
    line = mx_subLine(&mainCommand, command, my_command, &index);

    if (index.a > 0) {
        fd = mx_subExec(my_command, line);
        subFill(fd, index, &mainCommand, command);
        return mainCommand;
    }
    return command;
}
