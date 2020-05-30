#include "header.h"

static int cycleOne(t_inc *index, t_muteChar *trig, char *command, char **line) {
    if (command[(*index).c] == 96 && command[(*index).c - 1] != 92 && (*trig).dQ == false) {
        if ((*trig).sQ == false) {
            (*trig).sQ = true;
        }
        else {
            return -1;
        }
        return 1;
    }
    else if (command[(*index).c - 1] == 36 && command[(*index).c] == 40 && (*trig).sQ == false) {
        if ((*trig).dQ == false) {
            (*trig).dQ = true;
        }
        else {
            (*trig).iSs = true;
            (*line)[(*index).a] = command[(*index).c];
            (*index).a++;
        }
        return 1;
    }
    return 0;
}

static int cycleTwo(t_inc *index, t_muteChar *trig, char *command, char **mainCommand) {
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

static void closeString(char **line, t_inc *index, char **mainCommand, t_builtin_command *my_command) {
    (*line)[(*index).a] = '\0';
    (*mainCommand)[(*index).b] = ' ';
    (*line) = realloc((*line), strlen(*line) + 1);
    (*line) = mx_aliasSearch(*line, my_command->alias_list);
}

char *mx_subLine(char **mainCommand, char *command, t_builtin_command *my_command, t_inc *index) {
    t_muteChar trig;
    char *line = (char *)malloc(sizeof(char) * strlen(command));
    int check;

    memset(&trig, 0, sizeof(t_muteChar));
    for (; command[(*index).c] != '\0'; (*index).c++) {
        check = cycleOne(index, &trig, command, &line);
        if (check == 0) {
            check = cycleTwo(index, &trig, command, mainCommand);
            if (check == 0) {
                if (trig.sQ == true || trig.dQ == true) {
                    line[(*index).a] = command[(*index).c];
                    (*index).a++;
                }
            }
            if (check == -1)
                break;
        }
        if (check == -1)
            break;
    }
    closeString(&line, index, mainCommand, my_command);
    return line;
}
