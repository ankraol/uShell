#include "header.h"

static bool Extra(char *str, int i) {
    int count = 0;
    int j = 0;

    for (; j < i; j++) {
        if (str[j] == 96)
            return false;
    }
    for (j = mx_strlen(str) - 1; j > i; j--) {
        if (str[j] == 96)
            count++;
    }
    if (count == 1)
        return true;
    return false;
}

void mx_del_subSlash(char *str, int *i) {
    int count = 0;

    if (Extra(str, *i)) {
        for (int j = *i; str[j] == 92; j++)
            count++;
        if (count % 2 != 0)
            (*i) = (*i) + count;
    }
}
