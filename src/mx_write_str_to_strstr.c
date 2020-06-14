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

void mx_write_str_to_strstr(char ***s1, const char *s, char c, int b) {
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
