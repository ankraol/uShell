#include "header.h"

static bool Extra(char *str) {
    int count = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        // if (str[i] == 92 && str[i + 1] == 96)
        //     return true;
        if (str[i] == 92) {
            for (count = 0; str[i] == 92 && str[i] != '\0'; i++)
                count++;
            if (count > 3)
                return true;
        }
    }
    return false;
}

static int newSize(char *str) {
    int size = mx_strlen(str);
    int count = 0;
    // int extra = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        // if (str[i] == 92) {
        //     extra = i;
        //     mx_del_subSlash(str, &extra);
        //     size -= (extra - i);
        // }
        if (str[i] == 92) {
            for (count = 0; str[i] == 92 && str[i] != '\0'; i++)
                count++;
            if (count > 3)
                size -= (count / 4) * 2;
        }
    }
    return size;
}

static char *deleteExtra(char *str) {
    int size = newSize(str);
    char *newLine = (char *)malloc(sizeof(char) * (size + 1));
    int j = 0;
    int i = 0;
    int count = 0;

    for (i = 0; str[i] != '\0'; i++) {
        // if (str[i] == 92)
        //     mx_del_subSlash(str, &i);
        if (str[i] == 92) {
            for (count = 0; str[i] == 92 && str[i] != '\0'; i++)
                count++;
            i--;
            // printf("COUNT = %d\n", count);
            if (count > 3) {
                count -= (count / 4) * 2;
                // printf("NEW COUNT = %d\n", count);
                for (; count > 0; count--) {
                    newLine[j] = 92;
                    j++;
                }
            }
        }
        else {
            newLine[j] = str[i];
            j++;
        }
    }
    newLine[j] = '\0';
    return newLine;
}

// static bool slashSub(char *str) {
//     bool bQ = false;
//     int count;

//     for (int i = 0; str[i] != '\0'; i++) {
//         if (str[i] == 96 && str[i - 1] != 92) {
//             if (bQ)
//                 bQ = false;
//             else
//                 bQ = true;
//         }
//         else if (str[i] == 96 && str[i - 1] == 92 && !bQ) {
//             for (int j = i - 1; str[j] == 92; j--) {
//                 count++;
//             }
//             if (count % 2 != 0)
//                 return true;
//         }
//     }
//     return false;
// }

static char *strCopy(char *str) {
    char *copy = NULL;

    if (!Extra(str)) {
        // printf("NO EXTRA\n");
        copy = mx_strdup(str);
    }
    else
        copy = deleteExtra(str);
    // if (slashSub(copy))
        // mx_del_subSlash(&copy);
    return copy;
}

char *mx_jobDup(char *str) {
    if (!str)
        return NULL;
    return strCopy(str);
}
