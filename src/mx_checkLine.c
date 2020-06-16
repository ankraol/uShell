#include "header.h"

static void muteCheck(char line, t_muteChar *mute) {
    if (line == 34) {
        if ((*mute).dQ)
            (*mute).dQ = false;
        else
            (*mute).dQ = true;
    }
    else if (line == 39) {
        if ((*mute).sQ)
            (*mute).sQ = false;
        else
            (*mute).sQ = true;
    }
    else if (line == 96) {
        if ((*mute).iSs)
            (*mute).iSs = false;
        else
            (*mute).iSs = true;
    }
}

static bool nothing_in_line(char *line) {
    for (int i = 0; line[i] !='\0'; i++) {
        if (line[i] != 92 && line[i] != 34 && line[i] != ';' && line[i] != 39
            && line[i] != 36 && line[i] != 96 && line[i] != '|'
            && line[i] != '&' && line[i] != '{' && line[i] != '}'
            && line[i] != '(' && line[i] != ')' && line[i] != ' '
            && line[i] != '\r' && line[i] != '\t' && line[i] != '\n'
            && line[i] != '\v' && line[i] != '\f')
            {
                return false;
            }
    }
    return true;
}

bool mx_checkLine(char *line) {
    t_muteChar mute;

    memset(&mute, 0, sizeof(t_muteChar));
    if (nothing_in_line(line))
        return false;
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == 34 || line[i] == 39 || line[i] == 96)
            muteCheck(line[i], &mute);
    }
    if (mute.sQ || mute.dQ || mute.iSs) {
        fprintf(stderr, "ush: parse error\n");
        return false;
    }
    return true;
}
