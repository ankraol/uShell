#include "header.h"

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

    output = open(p->file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR
                            | S_IWUSR | S_ISUID);
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

void mx_for_redir_four(t_reddir **tasks, t_builtin_command *my_command, 
                            int *stat) {
    bool extInput = false;

    if ((tasks[0]->op == '|' || tasks[0]->output) && !tasks[0]->input)
        *stat = mx_pipe_rec(tasks, 0, 0, extInput, my_command);
    for_redir_one(tasks, my_command);
    for_redir_two(tasks);
}
