#include "header.h"

// static bool ommitChar(char *command, int *i) {
    // if (command[(*i)] == 92 && (command[(*i) + 1] == ' ' || command[(*i) + 1] == 34
        // || command[(*i) + 1] == 39 || command[(*i) + 1] == 36 || command[(*i) + 1] == 40
        // || command[(*i) + 1] == 41 || command[(*i) + 1] == 123 || command[(*i) + 1] == 125))
        // {
            // *i += 1;
            // return false;
        // }
    // else if (command[(*i)] == 92 && command[(*i) + 1] == 92) {
        // for (int j = 0; j < 4; j++) {
            // if (command[(*i) + 1] == 92)
                // *i += 1;
        // }
        // return false;
    // }
    // else if (command[(*i)] == ' ' && command[(*i) + 1] == ' ')
        // return true;
    // else
        // return false;
// }

static int countWords(const char *s, char c) {
    int count = 0;
    int size = strlen(s);
    bool iSsq = false;
    bool iSdq = false;

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == 34 && s[i - 1] != 92 && iSsq == false) {
            if (iSdq == false)
                iSdq = true;
            else
                iSdq = false;
        }
        else if (s[i] == 39 && iSdq == false) {
            if (iSsq == false)
                iSsq = true;
            else
                iSsq = false;
        }
        if (s[i] == c && s[i + 1] != c && s[i] == c && s[i + 1] != '\0'
        && iSdq == false && iSsq == false) {
            count++;
        }
    }
    if (s[0] == c && s[size] == c)
        count -= 1;
    else if (s[0] != c && s[size] != c)
        count += 1;
    return count;
}

char **mx_tokens(char *line, char sp) {
    int count = countWords(line, sp);
    char **tokens = (char **)malloc(sizeof (char *) * (count + 1));
    int len = 0;
    int st;
    int l = 0;
    bool iSsq = false;
    bool iSdq = false;

    // printf("START SPLIT\n");
    

    //echo " hello      \" hello     " <- that is wrong case
    printf ("\nWORDS -- %d\n\n", count);

    for (int i = 0; line[i] != '\0' && l < count; i++) {
            // printf("END = %d\n", i);
        // printf ("\nStart cycle -- \n");
        iSsq = false;
        iSdq = false;
        if (line[i] != sp) {
        if (line[i] == 34 && line[i - 1] != 92 && iSsq == false) {
            iSdq = true;
            //i++;
        }
        else if (line[i] == 39 && iSdq == false) {
            iSsq = true;
            //i++;
        }
        if (iSsq == false && iSdq == false) {
            // for(; line[i] == sp; i++);
            len = 0;
            for (int j = i; line[j] != sp && iSdq == false && iSsq == false
            && line[j] != '\0'; j++) {
                if (line[j] == 34 && line[j - 1] != 92 && iSsq == false) {
                    iSdq = true;
                    // len--;
                    break;
                }
                else if (line[j] == 39 && iSdq == false) {
                    iSsq = true;
                    // len--;
                    break;
                }
                len++;
            }
            // for (; line[i] == sp; i++);
        }
        else if (iSsq == true || iSdq == true) {
            len = 0;
            //  printf("i am here = %d\n", len);
            for (int j = i + 1; iSsq == true || iSdq == true; j++) {
                if (line[j] == 34 && line[j - 1] != 92 && iSsq == false) {
                    // printf("i am here now = %d\n", len);
                    iSdq = false;
                    // len--;
                    break;
                }
                else if (line[j] == 39 && iSdq == false) {
                    iSsq = false;
                    // len--;
                    break;
                }
                if (line[j] == 92 && line[j + 1] == 34)
                    len--;
                len++;
            }
            // for (; line[i] == sp; i++);
        }

        // printf("LENGTH = %d\n", len);

        tokens[l] = (char *)malloc(sizeof(char) * (len + 1));

        iSsq = false;
        iSdq = false;
        // printf("i  = %d\n", i);
        if (line[i] == 34 && line[i - 1] != 92 && iSsq == false) {
            iSdq = true;
            i++;
            // printf("i DQ = %d\n", i);
        }
        else if (line[i] == 39 && iSdq == false) {
            iSsq = true;
            i++;
        }

        if (iSsq == false && iSdq == false) {
            for (st = 0; line[i] != sp && iSdq == false && iSsq == false
            && line[i] != '\0'; i++, st++) {
                if (line[i] == 34 && line[i - 1] != 92 && iSsq == false) {
                    iSdq = true;
                    // i++;
                    break;
                }
                else if (line[i] == 39 && iSdq == false) {
                    iSsq = true;
                    // i++;
                    break;
                }
                tokens[l][st] = line[i];
            }
            // printf("WITHOUT QUOTES\n");
        }
        else if (iSsq == true || iSdq == true) {
            for (st = 0;(iSsq == true || iSdq == true)
            && line[i] != '\0'; st++) {
                if (line[i] == 34 && line[i - 1] != 92 && iSsq == false) {
                    iSdq = false;
                    // i++;
                    break;
                }
                else if (line[i] == 39 && iSdq == false) {
                    iSsq = false;
                    // i++;
                    break;
                }
                if (line[i] == 92 && line[i + 1] == 34) {
                    tokens[l][st] = line[i + 1];
                    i += 2;
                }
                else {
                    tokens[l][st] = line[i];
                    i++;
               }
            }
            // printf("WITH QUOTES\n");
        }

        // printf("AFTER SPLIT --> %s\n", tokens[l]);

        tokens[l][st] = '\0';
        // printf("AFTER SPLIT --> %s\n", tokens[l]);
        l++;
        
        }
        // else
            // printf("i sp = %d\n", i);

    }

    tokens[l] = NULL;
    // for (int i = 0; tokens[i]; i++) {
        // printf("parced COMMAND ==> %s\n", tokens[i]);
    // }
    return tokens;
}
// failed test cases :
// echo " hello      \" hello     "
//echo "  hello "
// echo "      || \" herev i am > "
