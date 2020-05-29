#include "header.h"

char *mx_subLine(char **mainCommand, char *command, t_builtin_command *my_command, t_inc *index) {
    t_muteChar trig;
    char *line = (char *)malloc(sizeof(char) * strlen(command));

    memset(&trig, 0, sizeof(t_muteChar));
    
    for (; command[(*index).c] != '\0'; (*index).c++) {
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
    }
    line[(*index).a] = '\0';
    (*mainCommand)[(*index).b] = ' ';
    line = realloc(line, strlen(line) + 1);
    line = mx_aliasSearch(line, my_command->alias_list);
    return line;
}
