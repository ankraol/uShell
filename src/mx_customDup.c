#include "header.h"

static bool Extra(char *str) {
    if (str[0] == ' ' || str[mx_strlen(str) - 1] == ' ')
        return true;
    return false;
}

static char *strCopy(char *str) {
    char *copy = NULL;

    if (!Extra(str))
        copy = mx_strdup(str);
    else
        copy = mx_delete_Extra(str);
    return copy;
}

char *mx_customDup(char *str) {
    if (!str)
        return NULL;
    return strCopy(str);
}
