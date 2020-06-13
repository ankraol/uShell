#include "header.h"

static bool isAlias(char *command) {
    if (command[0] == 'a' && command[1] == 'l' && command[2] == 'i'
        && command[3] == 'a' && command[4] == 's')
        {
            return true;
        }
    return false;
}

static void printVar(t_var *varList) {
    t_var *p = varList;

    printf("VARIABLES:\n");
    for (; p; p = p->next) {
        printf("NAME -> %s\n", (*p).name);
        printf("MEANS -> %s\n", (*p).meaning);
    }
    printf("END FOR NOW\n");
}

static void printAlias(t_alias *aliasList) {
    t_alias *p = aliasList;

    printf("Aliases:\n");
    for (; p; p = p->next) {
        printf("NAME -> %s\n", (*p).name);
        printf("MEANS -> %s\n", (*p).meaning);
    }
    printf("END FOR NOW\n");
}

static bool iSvar(char *task) {
    for (int i = 0; task[i] != '\0'; i++) {
        if (task[i] == '=' && task[i - 1] != ' ' && task[i + 1] != ' ')
            return true;
        else if (task[i] == ' ' || task[i] == '$')
            return false;
    }
    return false;
}

void deletePath(t_path **path) {
    t_path *p1 = *path;
    t_path *p2 = *path;

    for (; p1->next; p1 = p1->next);
    while (p1 != *path) {
        for (; p2->next != p1; p2 = p2->next);
        mx_strdel(&p1->file);
        free(p1);
        p1 = p2;
        p2 = *path;
    }
    mx_strdel(&(*path)->file);
    free(*path);
    *path = NULL;
}

void deleteTasks(t_reddir ***tasks) {
    int i = 0;

    for ( ; (*tasks)[i]; i++) {
        mx_strdel(&(*tasks)[i]->task);
        if ((*tasks)[i]->output)
            deletePath(&(*tasks)[i]->output);
        if ((*tasks)[i]->input)
            deletePath(&(*tasks)[i]->input);
        free((*tasks)[i]);
        (*tasks)[i] = NULL;
    }
    free(*tasks);
    *tasks = NULL;
}

static void for_redir_one(t_reddir **tasks, t_builtin_command *my_command) {
    int input;
    bool extInput = false;
    t_path *p = NULL;

    for (int i = 0; tasks[i]; i++) {
        if (tasks[i]->input) {
            p = tasks[i]->input;
            for (; p;  p = p->next) {
                input = open(p->file, O_RDONLY);
                if (input == -1)
                    perror("ush: ");
                extInput = true;
                mx_pipe_rec(tasks, i, input, extInput, my_command);
                extInput = false;
                close(input);
            }
        }
    }
}

static void for_redir_two_one(char *str, int size, t_path *p) {
    int output;

    output = open(p->file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_ISUID);
    if (output == -1)
        perror("ush");
    else
        write(output, str, size);
    close(output);
}

static void for_redir_two(t_reddir **tasks) {
    t_path *p = NULL;
    char *str = NULL;
    int size = 0;

    for (int i = 0; tasks[i]; i++) {
        if (tasks[i]->output != NULL) {
            if (tasks[i]->output->next) {
                str = mx_file_to_str(tasks[i]->output->file);
                size = strlen(str);
                p = tasks[i]->output->next;
                for (; p;  p = p->next)
                    for_redir_two_one(str, size, p);
                mx_strdel(&str);
            }
        }
    }
}

static void for_redir_three(t_reddir **tasks, t_builtin_command *my_command,
                            int *stat) {
    mx_varList(tasks[0]->task, &my_command->var);
    printVar(my_command->var);
    if (tasks[0]->task[0] == 'e' && tasks[0]->task[1] == 'x'
        && tasks[0]->task[2] == 'p' && tasks[0]->task[3] == 'o'
        && tasks[0]->task[4] == 'r' && tasks[0]->task[5] == 't')
        {
            my_command->execute = true;
            *stat = mx_ush_execute_env(tasks[0]->task, my_command, NULL, NULL);
        }
}

static void for_redir_four(t_reddir **tasks, t_builtin_command *my_command, 
                            int *stat) {
    bool extInput = false;

    if ((tasks[0]->op == '|' || tasks[0]->output) && !tasks[0]->input)
        *stat = mx_pipe_rec(tasks, 0, 0, extInput, my_command);
    for_redir_one(tasks, my_command);
    for_redir_two(tasks);
}

int mx_redirection(char *command, t_builtin_command *my_command) {
    t_reddir **tasks = mx_pipeCreate(command);
    int status = 0;

    if (tasks[0]->op == '|' || tasks[0]->output || tasks[0]->input)
        for_redir_four(tasks, my_command, &status);
    else {
        if (isAlias(tasks[0]->task) == true) {
            mx_aliasList(tasks[0]->task, &my_command->alias_list);
            printAlias(my_command->alias_list);
        }
        else if (iSvar(tasks[0]->task) == true)
            for_redir_three(tasks, my_command, &status);
        else {
            my_command->execute = true;
            status = mx_ush_execute_env(tasks[0]->task, my_command, NULL, NULL);
        }
    }
    deleteTasks(&tasks);
    return status;
}
