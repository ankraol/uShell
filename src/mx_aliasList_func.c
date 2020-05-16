#include "header.h"

static bool first(char *command, int *start, bool iSq) {
    if ((command[(*start)] == ' ' && iSq == false)
        || (command[(*start)] == 34 && iSq == true))
        {
            return true;
        }
    return false;
}

char *mx_nameCut(char *command, int *start) {
    char *name = (char *)malloc(sizeof(char) * strlen(command));
    int i = 0;
    bool iSq = false;

    for ( ; command[(*start)] != '='
        && command[(*start)] != '\0'; (*start)++)
        {
            if (command[(*start)] == 34 && iSq == false)
                iSq = true;
            else if (first(command, start, iSq))
                    break;
            else {
                name[i] = command[(*start)];
                i++;
            }
        }
    name[i] = '\0';
    name = realloc(name, strlen(name) + 1);
    return name;
}
