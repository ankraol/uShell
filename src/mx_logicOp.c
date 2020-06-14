#include "header.h"

static void isQuote(bool *dQ, bool *sQ, bool *ap, char *line, int i) {
    if (line[i] == 96 && line[i - 1] != 92 && !(*sQ) && !(*dQ)) {
        if ((*ap) == false)
            *ap = true;
        else
            *ap = false;
    }
    else if (((line[i] == 34 && line[i - 1] != 92)
    || (i == 0 && line[i] == 34)) && (*sQ) == false) {
        if ((*dQ) == false)
            *dQ = true;
        else
            *dQ = false;
    }
    else if (line[i] == 39 && (*dQ) == false) {
        if ((*sQ) == false)
            *sQ = true;
        else
            *sQ = false;
    }
}

static bool extraSpaces(char *line) {
    bool dQ = false;
    bool sQ = false;
    bool ap = false;

    for (int i = 0; line[i] != '\0'; i++) {
        isQuote(&dQ, &sQ, &ap, line, i);
        if (dQ == false && sQ == false && ap == false) {
            if (line[i] == ' ' && line[i + 1] == ' ')
                return true;
            else if (line[0] == ' ' || line[mx_strlen(line) - 1] == ' ')
                return true;
        }
    }
    return false;
}

static int innerCycle(char **newLine, t_queue **list, int i, int *start) {
    t_muteChar mute;

    memset(&mute, 0, sizeof(t_muteChar));
    if ((*newLine)[i] == 34 || (*newLine)[i] == 39 || (*newLine)[i] == 96)
        isQuote(&mute.dQ, &mute.sQ, &mute.iSs, (*newLine), i);
    if (mute.dQ == false && mute.sQ == false && mute.iSs == false
        && (((*newLine)[i] == '&' && (*newLine)[i + 1] == '&')
        || ((*newLine)[i] == '|' && (*newLine)[i + 1] == '|')))
        {
            mx_logic_pushBack(list, (*newLine), (*start), i - 1);
            for (;((*newLine)[i] == ' ' || (*newLine)[i] == '&'
                || (*newLine)[i] == '|')
                && (*newLine)[i] != '\0'; i++);
            (*start) = i;
        }
    return i;
}

void mx_logicOp(char *line, t_queue **list) {
    char *newLine = NULL;
    int start = 0;
    int i = 0;

    if (extraSpaces(line) == true) {
        newLine = mx_deleteExtraSpaces(line);
    }
    else {
        newLine = mx_strdup(line);
    }
    for (; newLine[i] != '\0'; i++) {
        i = innerCycle(&newLine, list, i, &start);
    }
    mx_logic_pushBack(list, newLine, start, i);
    mx_strdel(&newLine);
}

