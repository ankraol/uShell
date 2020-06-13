#include "header.h"

static bool Extra(char *str) {
    if (str[0] == ' ' || str[mx_strlen(str) - 1] == ' ')
        return true;
    return false;
}

static int newSize(char *str) {
    int size = mx_strlen(str);
    int i = 0;

    if (str[0] == ' ') {
        for (i = 0; str[i] == ' '; i++) {
            size--;
        }
    }
    if (str[size - 1] == ' ') {
        for (i = size - 1; str[i] == ' '; i--) {
            size--;
        }
    }
    return size;
}

static bool onlySpaces(char *str, int i) {
    for (int j = i; str[j] != '\0'; j++) {
        if (str[j] != ' ')
            return false;
    }
    return true;
}

static char *deleteExtra(char *str) {
    int size = newSize(str);
    char *newLine = (char *)malloc(sizeof(char) * (size + 1));
    int i = 0;
    int j = 0;

    if (str[0] == ' ')
        for (i = 0; str[i] == ' '; i++);
    for (; !onlySpaces(str, i) && str[i] != '\0'; i++) {
        newLine[j] = str[i];
        j++;
    }
    newLine[j] = '\0';
    return newLine;
}

static char *strCopy(char *str) {
    char *copy = NULL;

    if (!Extra(str))
        copy = mx_strdup(str);
    else
        copy = deleteExtra(str);
    return copy;
}

char *mx_customDup(char *str) {
    if (!str)
        return NULL;
    return strCopy(str);
}
