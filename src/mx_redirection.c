#include "header.h"

static bool isAlias(char *command) {
    if (command[0] == 'a' && command[1] == 'l' && command[2] == 'i'
        && command[3] == 'a' && command[4] == 's')
        {
            return true;
        }
    return false;
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

static void for_redir_three(t_reddir **tasks, t_builtin_command *my_command,
                            int *stat) {
    mx_varList(tasks[0]->task, &my_command->var);
    if (tasks[0]->task[0] == 'e' && tasks[0]->task[1] == 'x'
        && tasks[0]->task[2] == 'p' && tasks[0]->task[3] == 'o'
        && tasks[0]->task[4] == 'r' && tasks[0]->task[5] == 't')
        {
            my_command->execute = true;
            *stat = mx_ush_execute_env(tasks[0]->task, my_command, NULL, NULL);
        }
}

int mx_redirection(char *command, t_builtin_command *my_command) {
    t_reddir **task = mx_pipeCreate(command);
    int status = 0;

    if (task[0]->op == '|' || task[0]->output || task[0]->input)
        mx_for_redir_four(task, my_command, &status);
    else {
        if (isAlias(task[0]->task) == true)
            mx_aliasList(task[0]->task, &my_command->alias_list);
        else if (iSvar(task[0]->task) == true)
            for_redir_three(task, my_command, &status);
        else {
            my_command->execute = true;
            status = mx_ush_execute_env(task[0]->task, my_command, NULL, NULL);
        }
    }
    mx_deleteTasks(&task);
    return status;
}
