#include "header.h"

void mx_command_cut_one(t_reddir *tasks, int *arr, char *command,
                                bool *brr) {
    for (; arr[0] < arr[3]; arr[0]++) {
        mx_quotesCheck(&(brr[1]), &(brr[0]), command, arr[0]);
        if (((command[arr[0]] == '>' || command[arr[0]] == '<')
            && brr[0] == false && brr[0] == false) || command[arr[0]] == '\0')
            {
                break;
            }
        else if (command[arr[0]] == ' ' && (command[arr[0] + 1] == '>'
                || command[arr[0] + 1] == '<')
                && brr[0] == false && brr[0] == false)
                {
                    break;
                }
        else {
            tasks->task[arr[1]] = command[arr[0]];
            arr[1]++;
        }
    }
}

void mx_command_cut_nine(t_reddir *tasks, int *arr, int s, int f) {
    arr[0] = s;
    arr[3] = f;
    arr[4] = s;
    tasks->task = (char *)malloc(sizeof(char) * (arr[3] - arr[0]));
    tasks->input = NULL;
    tasks->output = NULL;
    // input = &tasks->input;
    // output = &tasks->output;
}


void mx_command_cut_ten(t_reddir *tasks, int *arr, char *com, bool *brr) {
    mx_command_cut_one(tasks, arr, com, brr);
    tasks->task[arr[1]] = '\0';
    tasks->task = realloc(tasks->task, strlen(tasks->task));
}

void mx_command_cut_eleven(t_path **output, char *command, int *arr,
                            bool *brr) {
    mx_command_cut_three(output, command, arr, arr[4]);
    mx_command_cut_four(command, arr, brr, output);
    mx_command_eight(arr, output);
}



void mx_command_cut_twelve(t_path **output, char *command, int *arr,
                            bool *brr) {
    mx_command_cut_two(command, arr, brr);
    if (command[arr[0]] == '>'&& arr[0] < arr[3]
        && brr[0] == false && brr[1] == false) {
        if (!(*output))
            *output = mx_create_list(command, &arr[0], arr[3], arr[4]);
        else
            mx_command_cut_eleven(output, command, arr, brr);
    }
}
