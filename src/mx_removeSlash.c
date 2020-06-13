#include "header.h"

static int newSize(char *str, char symb) {
    int size = strlen(str);

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == symb && str[i - 1] == 92)
            size -= 1;
    }
    return size;
}

void mx_removeSlash(char **str, char symb) {
    int size = newSize((*str), symb);
    char *newStr = (char *)malloc(sizeof(char) * (size + 1));
    int i = 0;
    int j = 0;

    for (; (*str)[i] != '\0'; i++) {
        if ((*str)[i] == 92 && (*str)[i + 1] == symb)
            i += 1;
        newStr[j] = (*str)[i];
        j++;
    }
    newStr[j] = '\0';
    mx_strdel(str);
    *str = mx_strdup(newStr);
    mx_strdel(&newStr);
}
