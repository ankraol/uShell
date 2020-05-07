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

static int tokensCount(char *command) {
    int count = 0;
    bool iSsq = false;
    bool iSdq = false;

    for (int i = 0; command[i] != '\0'; i++) {
        if (command[i] == 34 || command[i] == 39)
            quotesCheck(&iSsq, &iSdq, command, i);
        if (iSsq == false && iSdq == false
        && command[i] == ' ' && command[i + 1] != '\0')
            {
                count++;
            }
    }
    return count + 1;
}

// static char *tokenCut(char *command, int start, int end) {
//     char *token = (char *)malloc(sizeof(char) * (strlen(command) + 1));
//     int j = 0;
//     bool sQ = false;
//     bool dQ = false;

//     for (int i = start; i < end; i++) {
//         if (command[i] == 92 && command[i + 1] == 92)
//             for (int c = 0; command[i + 1] == 92 && c < 4; i++, c++);
//         else if (command[i] == 34 && command[i - 1] != 92 && sQ == false) {
//             // printf("DOUBLE QUOTES HERE %d\n", i);
//             i++;
//             if (dQ == false)
//                 dQ = true;
//             else
//                 dQ = false;
//         }
//         else if (command[i] == 39 && dQ == false) {
//             // printf("SINGLE QUOTES HERE %d\n", i);
//             i++;
//             if (sQ == false)
//                 sQ = true;
//             else
//                 sQ = false;
//         }
//         else if (command[i] == 92 && (command[i + 1] == 34
//             || command[i + 1] == 39 || command[i + 1] == 36 || command[i + 1] == 44
//             || command[i + 1] == 123 || command[i + 1] == 125 || command[i + 1] == 40
//             || command[i + 1] == 41))
//             {
//                 i++;
//             }
//         else if ((command[i] == 36 || command[i] == 44
//             || command[i] == 123 || command[i] == 125 || command[i] == 40
//             || command[i] == 41) && command[i - 1] != 92 && sQ == false && dQ == false)
//             {
//                 i++;
//             }
//             token[j] = command[i];
//             j++;
//     }
//     token[j] = '\0';
//     token = realloc(token, strlen(token) + 1);
//     printf("THAT`S WHAT WE HAVE - %s\n", token);
//     return token;
// }

// char **mx_tokenSplit(char *command) {
//     bool iSsq = false;
//     bool iSdq = false;
//     int q = 0;
//     int start = 0;
//     int i = 0;
//     int count = tokensCount(command);
//     char **tokens = (char **)malloc(sizeof(char *) * (count + 1));

//     // printf("WORDS IN %s - %d\n",command, count);
//     for (; command[i] != '\0'; i++) {
//         if (command[i] == 34 || command[i] == 39)
//             quotesCheck(&iSsq, &iSdq, command, i);
//         else if (command[i] == ' ' && iSsq == false && iSdq == false) {
//             tokens[q] = tokenCut(command, start, i);
//             printf("TOKEN %d - %s\n",q + 1,  tokens[q]);
//             start = i + 1;
//             q++;
//         }
//     }
//     tokens[q] = tokenCut(command, start, i);
//     printf("TOKEN %d - %s\n",q + 1,  tokens[q]);
//     tokens[q + 1] = NULL;
//     return tokens;
// }

char **mx_tokenSplit(char *command) {
    bool iSsq = false;
    bool iSdq = false;
    int arr[] = {0, 0, 0};
    int count = tokensCount(command);
    char **tokens = (char **)malloc(sizeof(char *) * (count + 1));

    for (; command[arr[2]] != '\0'; arr[2]++) {
        if (command[arr[2]] == 34 || command[arr[2]] == 39)
            quotesCheck(&iSsq, &iSdq, command, arr[2]);
        else if (command[arr[2]] == ' ' && iSsq == false && iSdq == false) {
            tokens[arr[0]] = mx_tokenCut(command, arr[1], arr[2]);
            arr[1] = arr[2] + 1;
            arr[0]++;
        }
    }
    tokens[arr[0]] = mx_tokenCut(command, arr[1], arr[2]);
    tokens[arr[0] + 1] = NULL;
    return tokens;
}
