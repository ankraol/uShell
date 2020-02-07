 #include "header.h"


int mx_ush_execute(char **argv) {
    pid_t pid;
    pid_t wpid;
    char *path = mx_read_env(argv[0]);
    int status;

    pid = fork();
    // printf("--%s\n ", path);

    if (pid == 0) {
         if (execvp(path, argv) == -1)
            perror("lsh");
        exit(1);
    }
    else
    {
         wpid = waitpid(pid, &status, WUNTRACED);
        // if (wpid == -1)
        if (status != 0)
            return 1;
            // printf("%d\n", status);
        // while (WIFEXITED(status) && WIFSIGNALED(status)) {
            // if (WIFEXITED(status) == 0)
                // printf("error");
            //  wpid = waitpid(pid, &status, WUNTRACED);
        // }
    }
    return 0;

}



char *mx_read_line() {
    char c;
    int bufsize = 1024;
    int position = 0;
    char *buffer = (char *)malloc(sizeof(char) * bufsize);

    while(1) {
        c = getchar();
        if (c == '\0' || c == '\n') {
            buffer[position] = '\0';
            return buffer;
        }
        else {
            buffer[position] = c;
        }
        position++;
    }
}

void lsh_loop(void) {
    char *line;
    char **args;
    int status = 2;
    t_tree *work = NULL;
    t_tree *p = NULL;

    while (1) {
        printf("super_shell: ");
        line = mx_read_line();
        work = mx_parcing(line);
        p = work;
        for (; (*p).right_child; p = (*p).right_child);
        if ((*p).parent) {
            p = (*p).parent;
            args = mx_strsplit((*(*p).right_child).command, ' ');
            status = mx_ush_execute(args);
            free(args);
            for (; p != NULL; p = (*p).parent) {
                if ((*p).operant[1] == '|') {
                    if (status == 1) {
                        args = mx_strsplit((*(*p).left_child).command, ' ');
                        status = mx_ush_execute(args);
                        free(args);
                    }
                }
                else if ((*p).operant[1] == '&') {
                    if (status == 0) {
                        args = mx_strsplit((*(*p).left_child).command, ' ');
                        status = mx_ush_execute(args);
                        free(args);
                    }
                }
            }
        }
        else
        {
            args = mx_strsplit((*p).command, ' ');
            status = mx_ush_execute(args);
            free(args);
        }
        free(line);
        // free(args);
    }
}


int main() {
  lsh_loop();
}


