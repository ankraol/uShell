#include "header.h"

static bool isExp(char *line) {
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == '$' && (line[i + 1] == '{' || line[i + 1] != '('))
            return true;
    }
    return false;
}

void mx_expandParameter(char *line) {
    if (isExp(line) == true)
        printf("THERE IS AN PARAMETER EXPANSION\n");
}
