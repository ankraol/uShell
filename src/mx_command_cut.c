#include "header.h"

static void quotesCheck(bool *sQ, bool *dQ, char *command, int i) {
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

static bool isSpace(char *command, int i) {
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

t_path *create_list(char *command, int *i, int f, int s) {
    t_path *p = NULL;
    int j = 0;
    // bool iSbl = false;
    // bool iSesc = false;

    p = (t_path *)malloc(sizeof(t_path));
    p->op = command[(*i)];
    for ((*i) += 1; command[(*i)] == ' '; (*i)++);
    p->file = (char *)malloc(sizeof(char) * (f - s));
    while ((*i) < f && command[(*i) + 1] != '<' && command[(*i) + 1] != '>') {
        if (isSpace(command, (*i)) == false) {
            // printf("let it in -> %c\n", command[(*i)]);
            p->file[j] = command[(*i)];
            (*i)++;
            j++;
        }
        else {
            (*i)++;
        }
    }
    p->file[j] = '\0';
    p->file = realloc(p->file, strlen(p->file));
    // printf("INPUT = %s\n", p->file);
    p->next = NULL;
    return p;
}

void mx_command_cut(char *command, int s, int f, t_reddir *tasks) {
    t_path **output = NULL;
    t_path **input = NULL;
    int i = s;
    int q = 0;
    int j = 0;
    bool iSdq = false;
    bool iSsq = false;

    tasks->task = (char *)malloc(sizeof(char) * (f - s));
    tasks->input = NULL;
    tasks->output = NULL;
    input = &tasks->input;
    output = &tasks->output;
    for (; i < f; i++) {
        quotesCheck(&iSsq, &iSdq, command, i);
        if (((command[i] == '>' || command[i] == '<')
            && iSdq == false && iSsq == false) || command[i] == '\0')
            {
                break;
            }
            else if (command[i] == ' ' && (command[i + 1] == '>' || command[i + 1] == '<')
                && iSdq == false && iSsq == false)
                {
                    break;
                }
            else {
                tasks->task[q] = command[i];
                q++;
            }
    }
    tasks->task[q] = '\0';
    tasks->task = realloc(tasks->task, strlen(tasks->task));
    // printf("%s\n", tasks->task);

        for (; i < f; i++) {
            if (command[i] == 34 && command[i - 1] != 92 && iSsq == false) {
                if (iSdq == false)
                    iSdq = true;
                else
                    iSdq = false;
            }
            else if (command[i] == 39 && iSdq == false) {
                if (iSsq == false)
                    iSsq = true;
                else
                    iSsq = false;
            }
            if (command[i] == '>'&& i < f && iSdq == false && iSsq == false) {
                if (!(*output)) {
                    *output = create_list(command, &i, f, s);
                }
                else {
                    for(; (*output)->next; output = &(*output)->next);
                    (*output)->next = (t_path *)malloc(sizeof(t_path));
                    (*output)->next->op = command[i];
                    for (i += 1; command[i] == ' '; i++);
                    (*output)->next->file = (char *)malloc(sizeof(char) * (f - s));
                    for (j = 0; i < f;) {
                        if (command[i] == 34 && command[i - 1] != 92 && iSsq == false) {
                            if (iSdq == false)
                                iSdq = true;
                            else
                                iSdq = false;
                        }
                        else if (command[i] == 39 && iSdq == false) {
                            if (iSsq == false)
                                iSsq = true;
                            else
                                iSsq = false;
                        }
                        if (iSsq == false && iSdq == false){
                            if (isSpace(command, i) == false){
                                (*output)->next->file[j] = command[i];
                                i++;
                                j++;
                            }
                            else
                                i++;
                        }
                        else if (iSsq == true || iSdq == true) {
                            (*output)->next->file[j] = command[i];
                            i++;
                            j++;
                        }
                        else if ((command[i] == '<' || command[i] == '>') && iSsq == false && iSdq == false)
                            break;
                    }
                    (*output)->next->file[j] = '\0';
                    (*output)->next->file = realloc((*output)->next->file, strlen((*output)->next->file));
                    (*output)->next->next = NULL;
                }
            }
            if (command[i] == '<' && i < f && iSsq == false && iSdq == false) {
                if (!(*input)) {
                    *input = create_list(command, &i, f, s);
                }
                else {
                    for(; (*output)->next; output = &(*output)->next);
                    (*output)->next = (t_path *)malloc(sizeof(t_path));
                    (*output)->next->op = command[i];
                    for (i += 1; command[i] == ' '; i++);
                    (*output)->next->file = (char *)malloc(sizeof(char) * (f - s));
                    for (j = 0; i < f;) {
                        if (command[i] == 34 && command[i - 1] != 92 && iSsq == false) {
                            if (iSdq == false)
                                iSdq = true;
                            else
                                iSdq = false;
                        }
                        else if (command[i] == 39 && iSdq == false) {
                            if (iSsq == false)
                                iSsq = true;
                            else
                                iSsq = false;
                        }
                        if (iSsq == false && iSdq == false){
                            if (isSpace(command, i) == false){
                                (*output)->next->file[j] = command[i];
                                i++;
                                j++;
                            }
                            else
                                i++;
                        }
                        else if (iSsq == true || iSdq == true) {
                            (*output)->next->file[j] = command[i];
                            i++;
                            j++;
                        }
                        else if ((command[i] == '<' || command[i] == '>') && iSsq == false && iSdq == false)
                            break;
                        }
                        (*input)->next->file[j] = '\0';
                        (*input)->next->file = realloc((*input)->next->file, strlen((*input)->next->file));
                        (*input)->next->next = NULL;
                }
            }
        }
}
