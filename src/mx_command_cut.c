#include "header.h"

void mx_quotesCheck(bool *sQ, bool *dQ, char *command, int i) {
    if (command[i] == 34 && command[i - 1] != 92 && (*sQ) == false) {
        if ((*dQ) == false)
            *dQ = true;
        else
            *dQ = false;
    }
    else if (command[i] == 39 && (*dQ) == false) {
        if ((*sQ) == false)
            *sQ = true;
        else
            *sQ = false;
    }
}



t_path *mx_create_list(char *command, int *i, int f, int s) {
    t_path *p = NULL;
    int j = 0;

    p = (t_path *)malloc(sizeof(t_path));
    p->op = command[(*i)];
    for ((*i) += 1; command[(*i)] == ' '; (*i)++);
    p->file = (char *)malloc(sizeof(char) * (f - s));
    while ((*i) < f && command[(*i) + 1] != '<' && command[(*i) + 1] != '>') {
        if (mx_isSpace(command, (*i)) == false) {
            p->file[j] = command[(*i)];
            (*i)++;
            j++;
        }
        else
            (*i)++;
    }
    p->file[j] = '\0';
    p->file = realloc(p->file, strlen(p->file) + 1);
    p->next = NULL;
    return p;
}

void mx_command_cut_two(char *com, int *arr, bool *brr) {
    if (com[arr[0]] == 34 && com[arr[0] - 1] != 92 && brr[1] == false) {
        if (brr[0] == false)
            brr[0] = true;
        else
            brr[0] = false;
    }
    else if (com[arr[0]] == 39 && brr[0] == false) {
        if (brr[1] == false)
            brr[1] = true;
        else
            brr[1] = false;
    }
}


void mx_command_cut_three(t_path **output, char *command, int *arr, int s) {
    for(; (*output)->next; output = &(*output)->next);
    (*output)->next = (t_path *)malloc(sizeof(t_path));
    (*output)->next->op = command[arr[0]];
    for (arr[0] += 1; command[arr[0]] == ' '; arr[0]++);
    (*output)->next->file = (char *)malloc(sizeof(char) * (arr[3] - s));
}

void mx_command_cut(char *command, int s, int f, t_reddir *tasks) {
    t_path **output = NULL;
    t_path **input = NULL;
    int arr[] = {0, 0, 0, 0, 0};
    bool brr[] = {false, false};

    mx_command_cut_nine(tasks, arr, s, f);
    input = &tasks->input;
    output = &tasks->output;
    mx_command_cut_ten(tasks, arr, command, brr);
    for (; arr[0] < f && command[arr[0]] != '\0'; arr[0]++) {
        mx_command_cut_twelve(output, command, arr, brr);
        if (mx_command_cut_fourteen(command, arr, brr)) {
            if (!(*input))
                *input = mx_create_list(command, &arr[0], f, s);
            else {
                mx_command_cut_thirteen(output, command, arr, brr);
                mx_command_seven(arr, input);
            }
        }
    }
}
