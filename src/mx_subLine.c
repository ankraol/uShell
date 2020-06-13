#include "header.h"

static int cycleTwo(t_inc *index, t_muteChar *trig, char *command,
                    char **mainCommand) {
    if (command[(*index).c] == 41) {
        if ((*trig).iSs == true)
            (*trig).iSs = false;
        else
            return -1;
        return 1;
    }
    else if ((*trig).sQ == false && (*trig).dQ == false) {
        if (command[(*index).c] != 36) {
            (*mainCommand)[(*index).b] = command[(*index).c];
            (*index).b++;
        }
        return 1;
    }
    return 0;
}

static void closeString(char **line, t_inc *index, char **mainCommand,
                        t_builtin_command *my_command) {
    (*line)[(*index).a] = '\0';
    (*mainCommand)[(*index).b] = ' ';
    (*line) = realloc((*line), strlen(*line) + 1);
    (*line) = mx_aliasSearch(*line, my_command->alias_list);
}

static void innerCycle(t_muteChar trig, t_inc *index, t_subCom commands) {
    int check;

    for (; commands.com[(*index).c] != '\0'; (*index).c++) {
        check = mx_cycleOne(index, &trig, commands.com, &commands.line);
        if (check == 0) {
            check = cycleTwo(index, &trig, commands.com, commands.origin);
            if (check == 0) {
                if (trig.sQ == true || trig.dQ == true) {
                    if (commands.com[(*index).c] == 92)
                        mx_del_subSlash(commands.com, &(*index).c);
                    commands.line[(*index).a] = commands.com[(*index).c];
                    (*index).a++;
                }
            }
            if (check == -1)
                break;
        }
        if (check == -1)
            break;
    }
}

char *mx_subLine(char **mainCommand, char *command,
                t_builtin_command *my_command, t_inc *index) {
    t_muteChar trig;
    char *line = (char *)malloc(sizeof(char) * strlen(command));
    t_subCom commands;

    memset(&trig, 0, sizeof(t_muteChar));
    commands.com = command;
    commands.line = line;
    commands.origin = mainCommand;
    innerCycle(trig, index, commands);
    closeString(&line, index, mainCommand, my_command);
    return line;
}
