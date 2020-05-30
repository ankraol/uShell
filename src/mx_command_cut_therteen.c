#include "header.h"


void mx_command_cut_thirteen(t_path **output, char *command, int *arr,
                             bool *brr) {
    mx_command_cut_five(output, command, arr, arr[4]);
    mx_command_cut_six(arr, command, output, brr);
}

bool mx_command_cut_fourteen( char *command, int *arr, bool *brr) {
    if (command[arr[0]] == '<' && arr[0] < arr[3] && brr[1] == false
        && brr[0] == false) {
        return true;
    }
    return false;
}
