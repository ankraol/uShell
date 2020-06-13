#include "header.h"

void mx_command_cut_five(t_path **output, char *com, int *arr, int s) {
    for(; (*output)->next; output = &(*output)->next);
    (*output)->next = (t_path *)malloc(sizeof(t_path));
    (*output)->next->op = com[arr[0]];
    for (arr[0] += 1; com[arr[0]] == ' ' && com[arr[0]] != '\0'; arr[0]++);
    (*output)->next->file = (char *)malloc(sizeof(char) * (arr[3] - s));
}

void static command_cut_six_one(char *com, int *arr, t_path **output) {
    if (mx_isSpace(com, arr[0]) == false){
        (*output)->next->file[arr[2]] = com[arr[0]];
        if (com[arr[0]] != '\0')
            arr[0]++;
        arr[2]++;
    }
    else {
        if (com[arr[0]] != '\0')
            arr[0]++;
    }
}

static bool command_cut_six_two(char *com, int *arr, bool *brr) {
    if ((com[arr[0]] == '<' || com[arr[0]] == '>') && brr[1] == false
        && brr[0] == false) {
        return true;
    }
    else
    {
        return false;
    }
    
}

void mx_command_cut_six(int *arr, char *com, t_path **output, bool *brr) {
    for (arr[2] = 0; arr[0] < arr[3];) {
        if (com[arr[0]] == 34 && com[arr[0] - 1] != 92 && brr[1] == false) {
            if (brr[0] == false)
                brr[0] = true;
        }
        else if (com[arr[0]] == 39 && brr[0] == false) {
            if (brr[1] == false)
                brr[1] = true;
        }
        if (brr[1] == false && brr[0] == false)
            command_cut_six_one(com, arr, output);
        else if (brr[1] == true || brr[0] == true) {
            (*output)->next->file[arr[2]] = com[arr[0]];
            if (com[arr[0]] != '\0')
                arr[0]++;
            arr[2]++;
        }
        else if (command_cut_six_two(com, arr, brr))
            break;
        }
}

void mx_command_eight(int *arr, t_path **output) {
    (*output)->next->file[arr[2]] = '\0';
    (*output)->next->file = realloc((*output)->next->file,
                            strlen((*output)->next->file));
    (*output)->next->next = NULL;
}
