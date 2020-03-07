#include "header.h"

static bool isAlias(char *command) {
    if (command[0] == 'a' && command[1] == 'l' && command[2] == 'i'
        && command[3] == 'a' && command[4] == 's')
        {
            return true;
        }
    return false;
}

static void quoteCheck(bool *sQ, bool *dQ, bool *iSs, char *command, int i) {
        if (command[i] == 96 && command[i - 1] != 92 && (*sQ) == false
            && (*dQ) == false)
            {
                if ((*iSs) == false)
                    *iSs = true;
                else
                    *iSs = false;
            }
        else if (command[i] == 34 && command[i - 1] != 92 && (*sQ) == false
            && (*iSs) == false)
            {
                if ((*dQ) == false)
                    *dQ = true;
                else
                    *dQ = false;
            }
        else if (command[i] == 39 && (*dQ) == false && (*iSs) == false) {
            if ((*sQ) == false)
                *sQ = true;
            else
                *sQ = false;
        }
}

static int dir_count(char *command) {
    int count = 0;
    bool iSdq = false;
    bool iSsq = false;
    bool iSs = false;

    for (int i = 0; command[i] != '\0'; i++) {
        quoteCheck(&iSsq, &iSdq, &iSs, command, i);
        if (command[i] == '|' && command[i + 1] != '|' && command[i - 1] != '|'
            && iSdq == false && iSsq  == false && iSs == false)
            {
                count++;
            }
    }
    return count;
}

static t_reddir *pipe_check(char *command) {
    int size = dir_count(command);
    t_reddir *tasks = (t_reddir *)malloc(sizeof(t_reddir) * (size + 2));
    int start = 0;
    int q = 0;
    int i = 0;
    bool iSdq = false;
    bool iSsq = false;
    bool iSsub = false;

    for (; command[i] != '\0'; i++) {
        quoteCheck(&iSsq, &iSdq, &iSsub, command, i);
        if (command[i] == '|' && command[i + 1] != '|' && command[i - 1] != '|'
            && iSdq == false && iSsq == false && iSsub == false)
            {
                tasks[q].input = NULL;
                tasks[q].output = NULL;
                if (command[i - 1] == ' ')
                    i -= 1;
                mx_command_cut(command, start, i, &tasks[q]);
                tasks[q].op = '|';
                for (; command[i] == ' ' || command[i] == '|'; i++);
                start = i;
                q++;
            }
    }
    tasks[q].input = NULL;
    tasks[q].output = NULL;
    mx_command_cut(command, start, i, &tasks[q]);
    tasks[q].op = '-';
    return tasks;
}

// static void printAlias(t_alias *list) {
    // t_alias *p = list;
// 
    // printf("ALIAS:\n");
    // for (; p; p = p->next) {
        // printf("NAME -> %s\n", (*p).name);
        // printf("MEANS -> %s\n", (*p).meaning);
    // }
    // printf("END FOR NOW\n");
// }

int mx_redirection(char *command, t_alias **aliasList) {
    // printf("redirection -> %s\n", command);
    t_reddir *tasks = pipe_check(command);
    int status = 2;
    int input;
    bool extInput = false;
    t_path *p = NULL;
    char *str = NULL;
    int size = 0;
    int output = 0;

    if (tasks[0].op == '|' || tasks[0].output || tasks[0].input) {
        if (tasks[0].op == '|' || tasks[0].output) {
            status = mx_pipe_rec(tasks, 0, 0, extInput);
        }
        for (int i = 0; tasks[i - 1].op != '-'; i++) {
            if (tasks[i].input) {
                p = tasks[i].input;
                for (; p;  p = p->next) {
                    input = open(p->file, O_RDONLY);
                    if (input == -1)
                        perror("ush");
                    extInput = true;
                    mx_pipe_rec(tasks, i, input, extInput);
                    extInput = false;
                    close(input);
                }
            }
        }
        for (int i = 0; tasks[i - 1].op != '-'; i++) {
            if (tasks[i].output != NULL) {
                if (tasks[i].output->next) {
                    // printf("EXTRA EXTERNAL OUTPUT\n");
                    str = mx_file_to_str(tasks[i].output->file);
                    size = strlen(str);
                    p = tasks[i].output->next;
                    for (; p;  p = p->next) {
                        output = open(p->file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_ISUID);
                        if (output == -1) {
                            perror("ush");
                        }
                        else {
                            write(output, str, size);
                        }
                        close(output);
                    }
                }
            }
        }
    }
    else {
        if (isAlias(tasks[0].task) == true) {
            // printf("ALIAS HERE\n");
            mx_aliasList(tasks[0].task, aliasList);
        }
        // else
            tasks[0].task = mx_aliasSearch(tasks[0].task, *aliasList);
            // printf("TASK -> %s\n", tasks[0].task);
            status = mx_ush_execute(tasks[0].task);
    }
    // printAlias(*aliasList);
    return status;
}
