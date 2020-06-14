#include "header.h"

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

char *mx_delete_Extra(char *str) {
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
