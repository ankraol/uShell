#include "libmx.h"

// char **mx_strsplit(const char *s, char c) {
//     const char *first;
//     char **arr = NULL;
//     int count = 0;
//     int len;
//     int st;
//     int l = 0;

//     if (s == NULL) {
//         return NULL;
//     }
//     int word = mx_count_words(s, c);
//     // printf("split\n");
    
//     first = s;
//     arr = (char **)malloc(sizeof (char *) * word + 1);
    
//     for (int i = 0; first[i] != '\0'; i++) {
//         if ((first[i] == c &&  first[i+1] != c && first[i+1] != '\0') || first[0] != c)  {
//             if (i != 0 || (i == 0 && first[i]  == c))
//                 i++;
//             count = i;
//             while (first[count] != c && first[count]  != '\0')
//                 count++;
//             len = count - i;
//             arr[l] = mx_strnew(len);
//             st = 0;
//             while (first[i] !=c && first[i]  != '\0') {
//                 arr[l][st] = first[i];
//                 st++;
//                 i++;
//             }
//             i--;
//             l++;
//         }
//     }
//     arr[l] = NULL;
//     return arr;
// }
void *mx_memcpy(void *restrict dst, const void *restrict src,
                size_t n) {
    char *p = (char *)dst;
    char *d = (char *)src;

    for (size_t i = 0; i < n; i++)
        p[i] = d[i];
    return dst;
}

char *mx_strndup(const char *s1, size_t n) {
    return mx_memcpy(mx_strnew(n), s1, n);
}

int mx_get_char_index(const char *str, char c) {
    if (str == 0)
        return - 2;
    for (int i = 0; str[i]; i++) {
        if (str[i] == c)
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
        while (mx_get_char_index(&s[i], c) == 0 && s[i] != '\0')
            i++;
        d = mx_get_char_index(&s[i], c);
        if (d > 0) {
            s2[a++] = mx_strndup(&s[i], d);
            i += d;
        }
        else {
            s2[a++] = mx_strndup(&s[i], mx_strlen(&s[i])); 
            i += d;
        }
    }
    s2[b] = 0;
    *s1 = s2;
}

char **mx_strsplit(const char *s, char c) {
    int b = 0;
    char **s1 = NULL;

    if (s == 0)
        return 0;
    b = mx_count_words(s, c);
    s1 = (char **)malloc((b + 1) * sizeof(char *));
    if (s1 != 0) { 
        write_str_to_strstr(&s1, s, c, b);
    }
    return s1;
}
