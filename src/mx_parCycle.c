#include "header.h"

static void thirdPart(char command, t_expChar trigg, t_expIndex *index, char **newLine) {
    if (trigg.exp == false && trigg.dollar == false) {
        (*newLine)[(*index).j] = command;
        (*index).j++;
    }
}

static int multiPart(char *command, int *i, t_expChar *triggers, bool *tilda) {
    int check = mx_par_firstPart(command, i, triggers, tilda);

    if (check == -1)
        return -1;
    else if (check == 0)
        check = mx_par_secondPart(command, i, triggers);
    return check;
}

static int secondPart(char command, t_expChar trigg, t_expIndex *index, char **expLine) {
    if (trigg.exp == true || trigg.dollar == true) {
        (*expLine)[(*index).k] = command;
        (*index).k++;
        return 1;
    }
    return 0;
}

char *mx_parCycle(t_expIndex *index, char *command, bool *tilda, char **newLine) {
    int i = (*index).start;
    char *expLine = (char *)malloc(sizeof(char) * strlen(command));
    t_expChar triggers;
    int check;

    memset(&triggers, 0, sizeof(t_expChar));
    for (; command[i] != '\0'; i++) {
            check = multiPart(command, &i, &triggers, tilda);
            if (check == -1)
                break;
            else if (check == 0)
                check = secondPart(command[i], triggers, index, &expLine);
                if (check == 0)
                    thirdPart(command[i], triggers, index, newLine);
    }
        (*index).start = i + 1;
        (*newLine)[(*index).j] = '\0';
        expLine[(*index).k] = '\0';
        expLine = realloc(expLine, strlen(expLine) + 1);
        return expLine;
}
