#include "header.h"

bool mx_isSpace(char *command, int i) {
    if (command[i] == ' ' && command[i - 1] != 92)
        return true;
    else if (command[i] == 92 && command[i - 1] != 92)
        return true;
    else if (command[i] == 34 && command[i - 1] != 92)
        return true;
    else if (command[i] == 39 && command[i - 1] != 92)
        return true;
    else if (command[i] == 36 && command[i - 1] != 92)
        return true;
    else if ((command[i] == 125 || command[i] == 123) && command[i - 1] != 92)
        return true;
    else if ((command[i] == 40 || command[i] == 41) && command[i - 1] != 92)
        return true;
    else
        return false;
}
static void command_cut_four_one(char *command, int *arr, t_path **output) {
    if (mx_isSpace(command, arr[0]) == false){
        (*output)->next->file[arr[2]] = command[arr[0]];
        arr[0]++;
        arr[2]++;
    }
    else
        arr[0]++;
}

static bool command_cut_four_two(char *com, int *arr, bool *brr) {
    if ((com[arr[0]] == '<' || com[arr[0]] == '>') 
        && brr[1] == false && brr[0] == false) {
        return true;
    }
    else
    {
        return false;
    }
    
}

void mx_command_cut_four(char *com, int *arr, bool *brr, t_path **output) {
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
            command_cut_four_one(com, arr, output);
        else if (brr[1] == true || brr[0] == true) {
            (*output)->next->file[arr[2]] = com[arr[0]];
            arr[0]++;
            arr[2]++;
        }
        else if (command_cut_four_two(com, arr, brr))
            break;
    }
}

void mx_command_seven(int *arr, t_path **input) {
    (*input)->next->file[arr[2]] = '\0';
    (*input)->next->file = realloc((*input)->next->file,
                            strlen((*input)->next->file));
    (*input)->next->next = NULL;
}


