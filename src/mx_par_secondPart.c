#include "header.h"

int mx_par_secondPart(char *command, int *i, t_expChar *trig) {
    if (command[(*i)] == 39 && (*trig).exp == false) {
        if ((*trig).sQ == false)
            (*trig).sQ = true;
        else
            (*trig).sQ = false;
        return 1;
    }
    else if (command[(*i)] == 125 && (*trig).exp == true) {
        (*trig).exp = false;
        return -1;
    }
    else if (command[(*i)] == ' ' && (*trig).dollar == true) {
        (*trig).dollar = false;
        i -= 1;
        return -1;
    }
    return 0;
}
