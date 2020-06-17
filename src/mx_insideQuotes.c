#include "header.h"

static bool isExp(char *line) {
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == 36)
            return true;
    }
    return false;
}

static bool doubleQuotes(char *line) {
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == 34)
            return true;
    }
    return false;
}

static char *deleteQuotes(char *line) {
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

static char *extractExpand(char *quoteLess, t_var *varList, int status) {
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

static char *returnQuotes(char *quoteLess) {
    char *newLine = (char *)malloc(sizeof(char) * (strlen(quoteLess) + 3));
    int i = 0;
    int j = 0;

    newLine[i] = 34;
    for (i = 1; quoteLess[j] != '\0'; j++) {
        newLine[i] = quoteLess[j];
        i++;
    }
    newLine[i] = 34;
    newLine[i + 1] = '\0';
    mx_strdel(&quoteLess);
    return newLine;
}

static char *expandLine(char *parameterLine, t_var *varList, int status) {
    char *expand = NULL;
    char *quoteLess = NULL;

    if (doubleQuotes(parameterLine)) {
        quoteLess = deleteQuotes(parameterLine);
        expand = extractExpand(quoteLess, varList, status);
        expand = returnQuotes(expand);
    }
    else {
        quoteLess = mx_strdup(parameterLine);
        expand = extractExpand(quoteLess, varList, status);
    }
    mx_strdel(&quoteLess);
    return expand;
}

static char *joinParts(char *first, char *second) {
    char *addspace = NULL;
    char *newLine = NULL;

    if (first)
        addspace = mx_strjoin(first, " ");
    newLine = mx_strjoin(addspace, second);
    if (first) {
        mx_strdel(&first);
        mx_strdel(&addspace);
    }
    return newLine;
}

char *mx_insideQuotes(char *line, t_var *varList, int status) {
    char **spaceSplited = mx_customSplit(line, ' ');
    char *expand = NULL;
    char *newLine = NULL;
    int i = 0;

    for (; spaceSplited[i]; i++) {
        if (isExp(spaceSplited[i])) {
            expand = expandLine(spaceSplited[i], varList, status);
            newLine = joinParts(newLine, expand);
            mx_strdel(&expand);
        }
        else
            newLine = joinParts(newLine, spaceSplited[i]);
    }
    mx_del_strarr(&spaceSplited);
    mx_strdel(&line);
    return newLine;
}
