#include "header.h"

static bool Extra(char *str) {
    int count = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == 92) {
            for (count = 0; str[i] == 92 && str[i] != '\0'; i++)
                count++;
            if (count > 3)
                return true;
        }
    }
    return false;
}

static char *strCopy(char *str) {
    char *copy = NULL;

    if (!Extra(str)) {
        copy = mx_strdup(str);
    }
    else
        copy = mx_job_deleteExtra(str);
    return copy;
}

char *mx_jobDup(char *str) {
    if (!str)
        return NULL;
    return strCopy(str);
}
