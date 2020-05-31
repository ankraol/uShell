#include "header.h"

static int partTwo(char *command, t_inc *index, t_muteChar *trig,
                    char **line) {
    if (command[(*index).c - 1] == 36 && command[(*index).c] == 40
        && (*trig).sQ == false)
        {
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

int mx_cycleOne(t_inc *index, t_muteChar *trig, char *command,
                char **line) {
    if (command[(*index).c] == 96 && command[(*index).c - 1] != 92
        && (*trig).dQ == false)
        {
            if ((*trig).sQ == false) {
                (*trig).sQ = true;
            }
            else {
                return -1;
            }
            return 1;
        }
        return partTwo(command, index, trig, line);
}
