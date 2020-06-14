#include "header.h"

static void QuotesCheck(const char *str, int i, t_muteChar *quotes) {
    if ((str[i] == 34 || str[i] == 39) && str[i - 1] != 92) {
        if (str[i] == 34) {
            if (quotes->dQ == false)
                quotes->dQ = true;
            else
                quotes->dQ = false;
        }
        else {
            if (quotes->sQ == false)
                quotes->sQ = true;
            else
                quotes->sQ = false;
        }
    }
}

static int countSeparator(const char *str, char c) {
    t_muteChar quotes;
    int count = 0;

    memset(&quotes, 0, sizeof(t_muteChar));
    for (int i = 0; str[i] != '\0'; i++) {
        QuotesCheck(str, i, &quotes);
        if (str[i] == c && str[i + 1] != c
            && quotes.sQ == false && quotes.dQ == false)
            {
                count++;
            }
    }
    return count;
}

static int count_words(const char *str, char c) {
    int size = mx_strlen(str);
    int count = 0;

    if (str == NULL) {
        return -1;
    }
    count = countSeparator(str, c);
    if (str[0] == c && str[size - 1] == c) {
        count -= 1;
    }
    if (str[0] != c && str[size - 1] != c) {
        count = count + 1;
    }
    return count;
}

char **mx_customSplit(const char *s, char c) {
    int b = 0;
    char **s1 = NULL;

    if (s == 0)
        return 0;
    b = count_words(s, c);
    if (b > 0)
        s1 = (char **)malloc((b + 1) * sizeof(char *));
    if (s1 != 0) { 
        mx_write_str_to_strstr(&s1, s, c, b);
    }
    return s1;
}
