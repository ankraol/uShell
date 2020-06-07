#include "header.h"

int mx_par_firstPart(char *command, int *i, t_expChar *trig, bool *tilda) {
    if ((command[(*i)] == 123 && command[(*i) - 1] == 36)
        && (*trig).sQ == false)
        {
            (*trig).exp = true;
            return 1;
        }
        else if (command[(*i)] == 36 && command[(*i) + 1] != 40
                && (*trig).sQ == false) 
                {
                    (*trig).dollar = true;
                    return 1;
                }
                else if (command[(*i)] == 126) {
                    if (command[(*i) + 1] == '+' || command[(*i) + 1] == '-')
                        (*i)++;
                    (*tilda) = true;
                    return -1;
                }
                return 0;
}
