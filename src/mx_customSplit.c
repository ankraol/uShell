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

static void *mem_cpy(void *restrict dst, const void *restrict src,
                size_t n) {
    char *p = (char *)dst;
    char *d = (char *)src;

    for (size_t i = 0; i < n; i++)
        p[i] = d[i];
    return dst;
}

static char *strn_dup(const char *s1, size_t n) {
    return mem_cpy(mx_strnew(n), s1, n);
}

static int get_char_index(const char *str, char c) {
    t_muteChar quotes;

    memset(&quotes, 0, sizeof(t_muteChar));
    if (str == 0)
        return - 2;
    for (int i = 0; str[i]; i++) {
        QuotesCheck(str, i, &quotes);
        if (str[i] == c && quotes.sQ == false && quotes.dQ == false)
            return i;
    }
    return - 1;
}

static void write_str_to_strstr(char ***s1, const char *s, char c, int b) {
    int a = 0;
    int d = 0;
    int i = 0;
    char **s2 = *s1; 
    
    while (a < b) {
        while (get_char_index(&s[i], c) == 0 && s[i] != '\0')
            i++;
        d = get_char_index(&s[i], c);
        if (d > 0) {
            s2[a++] = strn_dup(&s[i], d);
            i += d;
        }
        else {
            s2[a++] = strn_dup(&s[i], mx_strlen(&s[i])); 
            i += d;
        }
    }
    s2[b] = 0;
    *s1 = s2;
}

static int count_words(const char *str, char c) {
    int size = mx_strlen(str);
    int count = 0;
    t_muteChar quotes;

    memset(&quotes, 0, sizeof(t_muteChar));
    if (str == NULL) {
        return -1;
    }
    for (int i = 0; str[i] != '\0'; i++) {
        QuotesCheck(str, i, &quotes);
        if (str[i] == c && str[i + 1] != c
            && quotes.sQ == false && quotes.dQ == false)
            {
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


char **mx_customSplit(const char *s, char c) {
    int b = 0;
    char **s1 = NULL;

    if (s == 0)
        return 0;
    b = count_words(s, c);
    s1 = (char **)malloc((b + 1) * sizeof(char *));
    if (s1 != 0) { 
        write_str_to_strstr(&s1, s, c, b);
    }
    return s1;
}
