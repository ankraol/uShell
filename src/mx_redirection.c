#include "header.h"

static int pipes_count(char *command) {
    int count = 0;

    for (int i = 0; command[i] != '\0'; i++) {
        if (command[i] == '|') {
            count++;
        }
    }
    return count;
}

static char *command_cut(char *command, int s, int f) {
    char *extract = (char *)malloc(sizeof(char) * (f - s + 1));
    int i = s;
    int q = 0;

    for (; i < f; i++) {
        if (command[i] != ' ') {
            extract[q] = command[i];
            q++;
        }
    }
    extract[q] = '\0';
    return extract;
}

static char **pipe_check(char *command) {
    int size = pipes_count(command);
    printf("%d\n", size);
    char **tasks = (char **)malloc(sizeof(char *) * (size + 2));
    int start = 0;
    int q = 0;
    int i = 0;

    for (; command[i] != '\0'; i++) {
        if (command[i] == '|') {
            tasks[q] = command_cut(command, start, i);
            i ++;
            start = i;
            q++;
        }
    }
    printf("%d\n", start);
    printf("%d\n", i);
    tasks[q] = command_cut(command, start, i);
    tasks[q + 1] = NULL;
    return tasks;
}

void mx_redirection(char *command) {
    char **tasks = pipe_check(command);

    for (int i = 0; tasks[i] != NULL; i++) {
    }
}
