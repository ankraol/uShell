#include "header.h"

static char *varSearch(char *parameter, t_var *varList) {
    t_var *p = varList;
    char *varMeaning = NULL;

    for (; p; p = p->next) {
        if (mx_strcmp(parameter, (unsigned char *)p->name) == 0) {
            varMeaning = mx_strdup(p->meaning);
            return varMeaning;
        }
    }
    return NULL;
}

static int firstPart(char *command, int *i, t_expChar *trig, bool *tilda) {
    if ((command[(*i)] == 123 && command[(*i) - 1] == 36) && (*trig).sQ == false) {
        (*trig).exp = true;
        return 1;
    }
    else if (command[(*i)] == 36 && command[(*i) + 1] != 40 && (*trig).sQ == false) {
        (*trig).dollar = true;
        return 1;
    }
    else if (command[(*i)] == 126) {
        if (command[(*i) + 1] == '+' || command[(*i) + 1] == '-')
            (*i)++;
        (*tilda) = true;
        return -1;
   }
   return 0;
}

char *mx_parFill(char *command, char **newLine, t_expIndex *index, bool *tilda, t_var *varList) {
    int i = (*index).start;
    char *expLine = (char *)malloc(sizeof(char) * strlen(command));
    t_expChar triggers;
    char *replace = NULL;
    int check;

    memset(&triggers, 0, sizeof(t_expChar));
    for (; command[i] != '\0'; i++) {
            check = firstPart(command, &i, &triggers, tilda); 
            if (check == -1)
                break;
            else if (check == 0) {
            if (command[i] == 39 && triggers.exp == false) {
                if (triggers.sQ == false)
                    triggers.sQ = true;
                else
                    triggers.sQ = false;
            }
            else if (command[i] == 125 && triggers.exp == true) {
                triggers.exp = false;
                break;
            }
            else if (command[i] == ' ' && triggers.dollar == true) {
                triggers.dollar = false;
                i -= 1;
                break;
            }
            else if (triggers.exp == true || triggers.dollar == true) {
                expLine[(*index).k] = command[i];
                (*index).k++;
            }
            else if (triggers.exp == false && triggers.dollar == false) {
                    (*newLine)[(*index).j] = command[i];
                    (*index).j++;
            }
            }
        }
        (*index).start = i + 1;
        (*newLine)[(*index).j] = '\0';
        if ((*tilda) == false && expLine) {
            expLine[(*index).k] = '\0';
            expLine = realloc(expLine, strlen(expLine) + 1);
            replace = mx_parameterSearch(expLine, command);
            if (replace == NULL)
                replace = varSearch(expLine, varList);
        }
        else if ((*tilda) == true && expLine){
            if (command[(*index).start - 1] == '+')
                replace = mx_parameterSearch("PWD", command);
            else if (command[(*index).start - 1] == '-')
                replace = mx_parameterSearch("OLDPWD", command);
            else
                replace = mx_parameterSearch("HOME", command);
        }
        return replace;
}
