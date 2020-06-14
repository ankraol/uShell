#include "header.h"

static int newSize(char *str) {
    int size = mx_strlen(str);
    int count = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == 92) {
            for (count = 0; str[i] == 92 && str[i] != '\0'; i++)
                count++;
            if (count > 3)
                size -= (count / 4) * 2;
        }
    }
    return size;
}

static int removeSlashes(char *str, char **newLine, int i, int *j) {
    int count;

    for (count = 0; str[i] == 92 && str[i] != '\0'; i++)
        count++;
    i--;
    if (count > 3) {
        count -= (count / 4) * 2;
        for (; count > 0; count--) {
            (*newLine)[(*j)] = 92;
            (*j)++;
        }
    }
    return i;
}

char *mx_job_deleteExtra(char *str) {
    int size = newSize(str);
    char *newLine = (char *)malloc(sizeof(char) * (size + 1));
    int j = 0;
    int i = 0;

    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == 92)
            i = removeSlashes(str, &newLine, i, &j);

        else {
            newLine[j] = str[i];
            j++;
        }
    }
    newLine[j] = '\0';
    return newLine;
}
