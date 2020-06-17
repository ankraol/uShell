#include "header.h"

static void quotesCheck(bool *iSsq, bool *iSdq, char *command, int i) {
    if (command[i] == 34 && command[i - 1] != 92 && (*iSsq) == false) {
        if ((*iSdq) == false)
            *iSdq = true;
        else
            *iSdq = false;
    }
    else if (command[i] == 39 && (*iSdq) == false) {
        if ((*iSsq) == false)
            *iSsq = true;
        else
            *iSsq = false;
    }
}

static bool onlySpaces(char *line, int i) {
    for (int j = i; line[j] != '\0'; j++) {
        if (line[j] != ' ')
            return false;
    }
    return true;
}

static int tokensCount(char *command) {
    int count = 0;
    bool iSsq = false;
    bool iSdq = false;

    for (int i = 0; command[i] != '\0'; i++) {
        if (command[i] == 34 || command[i] == 39)
            quotesCheck(&iSsq, &iSdq, command, i);
        if (iSsq == false && iSdq == false
        && command[i] == ' ' && command[i + 1] != '\0'
        && command[i - 1] != 92 && !onlySpaces(command, i))
            {
                count++;
            }
    }
    return count + 1;
}

char **mx_tokenSplit(char *command) {
    bool iSsq = false;
    bool iSdq = false;
    int arr[] = {0, 0, 0};
    int count = tokensCount(command);
    char **tokens = (char **)malloc(sizeof(char *) * (count + 1));

    for (; command[arr[2]] != '\0'; arr[2]++) {
        if (command[arr[2]] == 34 || command[arr[2]] == 39)
            quotesCheck(&iSsq, &iSdq, command, arr[2]);
        else if (command[arr[2]] == ' ' && iSsq == false && iSdq == false
                && command[arr[2] - 1] != 92 && !onlySpaces(command, arr[2]))
                {
                    tokens[arr[0]] = mx_tokenCut(command, arr[1], arr[2]);
                    arr[1] = arr[2] + 1;
                    arr[0]++;
                }
        }
        tokens[arr[0]] = mx_tokenCut(command, arr[1], arr[2]);
        tokens[arr[0] + 1] = NULL;
        return tokens;
}
