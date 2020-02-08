 #include "header.h"


int mx_ush_execute(char **argv) {
    pid_t pid;
    pid_t wpid;
    char *path = mx_read_env(argv[0]);
    int status;
    
    
    pid = fork();
    if (pid == 0) {        
        if (execvp(path, argv) == -1)
            perror("lsh");
                exit(1);
    }
    else
    {
         wpid = waitpid(pid, &status, WUNTRACED);
        if (status != 0)
            return 1;
    }
    return 0;
}

int mx_ush_pipe_execute() {
    pid_t pid;
    pid_t wpid;
    //char *path = mx_read_env(argv[0]);
    char *argv[] = { "/bin/ls", "-l", 0 };
    char *argv_2[] = { "/bin/grep", "M", 0 };
    int status;
    int fd[2];

    pipe(fd);
    pid = fork();
    if (pid == 0) {
        dup2(fd[1], 1);
        close(fd[1]);
        close(fd[0]);
        if (execvp("ls", argv) == -1)
            perror("lsh");
        //exit(EXIT_FAILURE);
    }
    else
    {
        pid=fork();
        if (pid == 0) {
            dup2(fd[0], 0);
            close(fd[1]);
            close(fd[0]);
            if (execvp("grep", argv_2) == -1)
                perror("lsh");

        }
        else {
            close(fd[1]);
            close(fd[0]);  
        wpid = waitpid(pid, &status, WUNTRACED);
        while (WIFEXITED(status) && WIFSIGNALED(status))
            wpid = waitpid(pid, &status, WUNTRACED);
        }
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
    // char **args;
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
            mx_redirection((*(*p).right_child).command);
            // args = mx_strsplit((*(*p).right_child).command, ' ');
            // status = mx_ush_execute(args);
            // free(args);
            for (; p != NULL; p = (*p).parent) {
                if ((*p).operant[1] == '|') {
                    if (status == 1) {
                        mx_redirection((*(*p).left_child).command);
                        // args = mx_strsplit((*(*p).left_child).command, ' ');
                        // status = mx_ush_execute(args);
                        // free(args);
                    }
                }
                else if ((*p).operant[1] == '&') {
                    if (status == 0) {
                        mx_redirection((*(*p).left_child).command);
                        // args = mx_strsplit((*(*p).left_child).command, ' ');
                        // status = mx_ush_execute(args);
                        // free(args);
                    }
                }
            }
        }
        else
        {
            mx_redirection((*p).command);
            // args = mx_strsplit((*p).command, ' ');
            // status = mx_ush_execute(args);
            // free(args);
        }
        free(line);
        // free(args);
    }
}


int main() {
    lsh_loop();
    //lsh_loop();
    mx_ush_pipe_execute(); 
    
}


