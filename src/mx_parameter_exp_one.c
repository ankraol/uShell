#include "header.h"


static bool first(char *command, int i, bool sQ) {
    if (command[i] == 123 && command[i - 1] == 36 && command[i - 2] != 92
        && sQ == false)
        {
            return true;
        }
    return false;
}

static bool second(char *command, int i, bool sQ, bool dQ) {
    if (command[i] == 36 && (command[i + 1] != ' ' || command[i + 1] != '\0')
        && sQ == false && command[i - 1] != 92)
        {
            return true;
        }
    else if (command[i] == 126 && sQ == false
            && dQ == false && command[i - 1] != 92)
        {
            return true;
        }
    return false;
}

bool mx_parExt(char *command) {
    bool sQ = false;
    bool dQ = false;

    for (int i = 0; command[i] != '\0'; i++) {
        if (first(command, i, sQ))
            return true;
        else if (command[i] == 39 && dQ == false) {
            if (sQ == false)
                sQ = true;
        }
        else if (command[i] == 34 && command[i - 1] != 92 && sQ == false) {
            if (dQ == false)
                dQ = true;
        }
        else if (second(command, i, sQ, dQ))
            return true;
    }
    return false;
}
