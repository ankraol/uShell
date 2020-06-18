#include "header.h"

static void subFill(int fd, t_inc i, char **mainCommand, char *com) {
    char c;

    for(; read(fd, &c, 1); i.b++) {
        if (c == '\n')
            c = ' ';
        (*mainCommand)[i.b] = c;
    }
    close(fd);
    if ((*mainCommand)[i.b - 1] == ' ')
        i.b -= 1;
    for (i.c += 1; com[i.c] != '\0' && com[i.c - 1] != '\0'; i.c++) {
        (*mainCommand)[i.b] = com[i.c];
        i.b++;
    }
    if ((*mainCommand)[i.b - 1] == ' ')
        (*mainCommand)[i.b - 1] = '\0';
    else
        (*mainCommand)[i.b] = '\0';
    (*mainCommand) = realloc(*mainCommand, strlen(*mainCommand) + 1);
}

char *mx_substitute(char *command, t_builtin_command *my_command) {
    int fd;
    t_inc index;
    char *mainCommand = (char *)malloc(sizeof(char) * strlen(command) * 50);
    char *line = NULL;

    
    command = mx_aliasSearch(command, my_command->alias_list);
    memset(&index, 0, sizeof(t_inc));
    line = mx_subLine(&mainCommand, command, &index);
    if (index.a > 0 && mx_checkLine(line)) {
        fd = mx_subExec(my_command, line);
        subFill(fd, index, &mainCommand, command);
        mainCommand = mx_substitute(mainCommand, my_command);
        if (malloc_size(command))
            mx_strdel(&command);
        return mainCommand;
    }
    if (malloc_size(line))
        mx_strdel(&line);
    if(malloc_size(mainCommand))
        mx_strdel(&mainCommand);
    return command;
}
