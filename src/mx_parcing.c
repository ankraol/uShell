#include "header.h"

static char *operant_cut(char *input, int f, char c) {
    char *buf = NULL;
    int j = 0;
    int i = f;
    int s = 0;

    for (; input[i] == c; i--);
    s = i;
    buf = (char *)malloc(sizeof(char) * (f - s));
    for (; i <= f; i++, j++) {
        buf[j] = input[i];
    }
    buf[j] = '\0';
    return buf;
}

static bool onlySpaces(char *command, int start, int end) {
    for (int i = start; i <= end; i++) {
        if (command[i] !=' ')
            return false;
    }
    return true;
}

static char *command_cut(char *input, int s, int f) {
    char *buf = (char *)malloc(sizeof(char) * (f - s));
    int j = 0;
    // bool iSesc = false;

    for (int i = s + 1; i <= f;) {
        if (onlySpaces(input, i, f) == false) {
            buf[j] = input[i];
            i++;
            j++;
        }
        else
            i++;
    }
    buf[j] = '\0';
    return buf;
}

t_tree *mx_parcing(char *input) {
    t_tree *work = (t_tree *)malloc(sizeof(t_tree));
    t_tree *p = NULL;
    t_tree *parent = NULL;
    int size = strlen(input);
    bool iSdq = false;
    bool iSsq = false;

    (*work).parent = parent;
    for (int i = strlen(input) - 1; i >= 0; i--) {
        if (input[i] == 39 && iSdq == false) {
            if (iSsq == false) {
                // printf("OPEN SINGLE QUOTES - %d\n", i);
                iSsq = true;
            }
            else if (iSsq == true) {
                // printf("CLOSE SINGLE QUOTES - %d\n", i);
                iSsq = false;
            }
        }
        else if (input[i] == 34 && input[i - 1] != 92 && iSsq == false) {
            if (iSdq == false) {
                // printf("OPEN DOUBLE QUOTES - %d\n", i);
                iSdq = true;
            }
            else if (iSdq == true) {
                // printf("CLOSE DOUBLE QUOTES - %d\n", i);
                iSdq = false;
            }
        }

        if (input[i] == '|' && input[i - 1] == '|' && iSdq == false && iSsq == false) {
            // printf("NOT SUPPOSED TO BE HERE - %d\n", i);
            parent = work;
            (*work).operant = operant_cut(input, i, '|');
            (*work).command = NULL;
            (*work).left_child = (t_tree *)malloc(sizeof(t_tree));
            p = (*work).left_child;
            (*p).parent = parent;
            (*p).operant = NULL;
            (*p).command = command_cut(input, i, size);
            (*work).right_child = (t_tree *)malloc(sizeof(t_tree));
            (*(*work).right_child).parent = parent;
            work = (*work).right_child;
            for (; input[i] == '|'; i--);
            size = i;
        }
        else if (input[i] == '&' && input[i - 1] == '&' && iSdq == false && iSsq == false) {
            parent = work;
            (*work).operant = operant_cut(input, i, '&');
            (*work).command = NULL;
            (*work).left_child = (t_tree *)malloc(sizeof(t_tree));
            p = (*work).left_child;
            (*p).parent = parent;
            (*p).operant = NULL;
            (*p).command = command_cut(input, i, size);
            (*work).right_child = (t_tree *)malloc(sizeof(t_tree));
            (*(*work).right_child).parent = parent;
            work = (*work).right_child;
            for (; input[i] == '&'; i--);
            size = i;
        }
    }
    (*work).operant = NULL;
    // printf("%s - %d\n", input, size);
    (*work).command = command_cut(input, -1, size);
    // printf("%s\n", (*work).command);
    (*work).parent = parent;
    (*work).left_child = NULL;
    (*work).right_child = NULL;
    return work;
    // out(work);
}
