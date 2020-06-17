#include "header.h"

static int sizeof_extract(char *quoteLess) {
    int size = 0;
    bool dollar = false;

    for (int i = 0; quoteLess[i] != '\0'; i++) {
        if (quoteLess[i] == 36) {
            if (!dollar)
                dollar = true;
            else
                break;
        }
        else if (dollar && quoteLess[i] == ' ')
            break;
        else if (dollar)
            size++;
    }
    return size;
}

static int findDollar(char *quoteLess) {
    int i = 0;

     for ( ; quoteLess[i] != '\0'; i++) {
        if (quoteLess[i] == 36)
            break;
    }
    return i;
}

static char *deleteBrackets(char *line) {
    char *newLine = (char *)malloc(sizeof(char *) * (strlen(line) - 1));
    int i = 1;
    int j = 0;

    for (; line[i + 1] != '\0'; i++) {
        newLine[j] = line[i];
        j++;
    }
    newLine[j] = '\0';
    return newLine;
}

static char *exp_parameter(char *line, t_var *varList, int status) {
    int size = sizeof_extract(line);
    int d_l = findDollar(line);
    char *par = strndup((const char *)(line + d_l + 1), size);
    char *bracketless = NULL;
    char *meaning = NULL;

    if (par[0] == '{')
        bracketless = deleteBrackets(par);
    else
        bracketless = mx_strdup(par);
    meaning = mx_findParameter(bracketless, varList, status);
    mx_strdel(&par);
    mx_strdel(&bracketless);
    return meaning;
}

static char *combineParts(char *first, char *second, char *third) {
    char *firstpart = NULL;
    char *newLine = NULL;

    firstpart = mx_strjoin(first, second);
    if (malloc_size(first))
        mx_strdel(&first);
    if(malloc_size(second))
        mx_strdel(&second);
    newLine = mx_strjoin(firstpart, third);
    mx_strdel(&firstpart);
    if (malloc_size(third))
        mx_strdel(&third);
    return newLine;
}

char *mx_extractExpand(char *quoteLess, t_var *varList, int status) {
    int size = sizeof_extract(quoteLess);
    char *before_extr = NULL;
    char *after_extr = NULL;
    int d_l = findDollar(quoteLess); ///dollar location;
    char *meaning = exp_parameter(quoteLess, varList, status);
    char *newLine = NULL;

    if (d_l != 0)
        before_extr = strndup((const char *)quoteLess, d_l);
    if ((d_l + size) < mx_strlen(quoteLess))
        after_extr = mx_strdup((quoteLess + (d_l + size + 1)));
    newLine = combineParts(before_extr, meaning, after_extr);
    return newLine;
}
