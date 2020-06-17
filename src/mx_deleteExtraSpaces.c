#include "header.h"

static void isQuote(bool *dQ, bool *sQ, bool *ap, char *line, int i) {
    if (line[i] == 96 && line[i - 1] != 92 && !(*sQ) && !(*dQ)) {
        if ((*ap) == false)
            *ap = true;
        else
            *ap = false;
    }
    else if (((line[i] == 34 && line[i - 1] != 92)
    || (i == 0 && line[i] == 34)) && (*sQ) == false) {
        if ((*dQ) == false)
            *dQ = true;
        else
            *dQ = false;
    }
    else if (line[i] == 39 && (*dQ) == false) {
        if ((*sQ) == false)
            *sQ = true;
        else
            *sQ = false;
    }
}

static bool onlySpaces (char *line, int i) {
    for(; line[i] != '\0'; i++) {
        if (line[i] != ' ')
            return false;
    }
    return true;
}

static int omitSpaces(char *line, int i) {
    if (line[i] == ' ') {
        if (i == 0)
            for (; line[i] == ' '; i++);
        else if (line[i + 1] == '\0')
            return -1;
        else if (onlySpaces(line, i) == true)
            return -1;
        else
            for(; line[i + 1] == ' '; i++);
    }
    return i;
}

char *mx_deleteExtraSpaces(char *line) {
    char *newLine = (char *)malloc(sizeof(char) * strlen(line) + 1);
    bool dQ = false;
    bool sQ = false;
    bool ap = false;
    int j = 0;

    for (int i = 0; line[i] != '\0'; i++, j++) {
        isQuote(&dQ, &sQ, &ap, line, i);
        if (!dQ && !sQ && !ap)
            i = omitSpaces(line, i);
        if (i == -1)
            break;
        newLine[j] = line[i];
    }
    newLine[j] = '\0';
    newLine = realloc(newLine, strlen(newLine) + 1);
    return newLine;
}
