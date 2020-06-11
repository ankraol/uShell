#include "header.h"

static void thirdPart(char command, t_expChar trigg, t_expIndex *index, char *newLine) {
    if (trigg.exp == false && trigg.dollar == false) {
        // printf("space? - %c\n", command);
        newLine[(*index).j] = command;
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
    fprintf(stdout, "COMMAND(parCycle) start = %s\n", command);
    for (; i < mx_strlen(command); i++) {
        check = multiPart(command, &i, &triggers, tilda);
        fprintf(stdout, "COMMAND(parCycle) multipart = %s, check = %d\n", command, check);
        if (check == -1)
            break;
        else if (check == 0) {
            check = secondPart(command[i], triggers, index, &expLine);
            fprintf(stdout, "COMMAND(parCycle) secondPart = %s, check = %d\n", command, check);
            if (check == 0) {
                thirdPart(command[i], triggers, index, *newLine);
                fprintf(stdout, "COMMAND(parCycle) thirdPart = %s\n", command);
            }
        }
    }
    fprintf(stdout, "COMMAND(parCycle) after cycle = %s\n", command);
    fprintf(stdout, "cycle ended in parCycle\n");
    if (command[i] == '\0')
        (*index).start = i;
    else
        (*index).start = i + 1;
    printf("AFTER CYCLE -> %c\n", command[(*index).start]);
    (*newLine)[(*index).j] = '\0';
    expLine[(*index).k] = '\0';
    expLine = realloc(expLine, strlen(expLine) + 1);
    fprintf(stdout, "COMMAND(parCycle) end = %s\n", command);
    return expLine;
}
