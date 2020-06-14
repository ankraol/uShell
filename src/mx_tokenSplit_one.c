#include "header.h"

static bool first(char *command, int *i, bool *sQ, bool *dQ) {
    if (command[*i] == 34 && command[(*i) - 1] != 92 && *sQ == false) {
        (*i)++;
        if (*dQ == false)
            *dQ = true;
        else
            *dQ = false;
        return true;
    }
    else if (command[*i] == 39 && *dQ == false) {
        (*i)++;
        if (*sQ == false)
            *sQ = true;
        else
            *sQ = false;
        return true;
    }
    return false;
}

static bool second(char *command, int *i, bool *sQ, bool *dQ) {
    if (command[(*i)] == 92 && (command[(*i) + 1] == 34
        || command[(*i) + 1] == 39 || command[(*i) + 1] == 36
        || command[(*i) + 1] == 44 || command[(*i) + 1] == 123
        || command[(*i) + 1] == 125 || command[(*i) + 1] == 40
        || command[(*i) + 1] == 41 || command[(*i) + 1] == ' '
        || command[(*i) + 1] == 96 || command[(*i) + 1] == 33) && !(*sQ))
        {
           (*i) = (*i) + 1;
            return true;
        }
    else if ((command[(*i)] == 36 || command[(*i)] == 44
        || command[(*i)] == 123 || command[(*i)] == 125
        || command[(*i)] == 40 || command[(*i)] == 41)
        && command[(*i) - 1] != 92 && sQ == false && dQ == false)
        {
            (*i)++;
            return true;
        }
    return false;
}

char *mx_tokenCut(char *command, int start, int end) {
    char *token = (char *)malloc(sizeof(char) * (strlen(command) + 1));
    int j = 0;
    bool sQ = false;
    bool dQ = false;

    for (int i = start; i < end && command[i] != '\0'; i++) {
        if (command[i] == 92 && command[i + 1] == 92) {
            i++;
        }
        else if (first(command, &i, &sQ, &dQ));
        else if (second(command, &i, &sQ, &dQ)){
        }
        if (command[i] == '\0')
            break;
        token[j] = command[i];
        j++;
    }
    token[j] = '\0';
    token = realloc(token, strlen(token) + 1);
    return token;
}
