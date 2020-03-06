#include "header.h"

int mx_count_words(const char *str, char c) {
    int size = mx_strlen(str);
    int count = 0;

    if (str == NULL) {
        return -1;
    }
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c && str[i + 1] != c) {
            count++;
        }
    }
    if (str[0] == c && str[size - 1] == c) {
        count -= 1;
    }
    if (str[0] != c && str[size - 1] != c) {
        count = count + 1;
    }
    return count;
}
