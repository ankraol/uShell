 #include "header.h"


int mx_ush_execute(char **argv) {
    pid_t pid;
    pid_t wpid;
    char *path = mx_read_env(argv[0]);
    int status;
    int file_pipes[2];

    pipe(file_pipes);
    pid = fork();
    if (pid == 0) {
        dup2(file_pipes[1], 1);
        if (execvp(path, argv) == -1)
            perror("lsh");
        //exit(EXIT_FAILURE);
    }
    else
    {
        wpid = waitpid(pid, &status, WUNTRACED);
        while (WIFEXITED(status) && WIFSIGNALED(status))
            wpid = waitpid(pid, &status, WUNTRACED);
    }
    return 1;

}

// int mx_ush_pipe_execute(char ***argv) {
//     pid_t pid;
//     pid_t wpid;

//     int status;
//     int fd[2];

//     pipe(fd);
//     pid = fork();
//     if (pid == 0) {
//         dup2(fd[1], 1);
//         close(fd[1]);
//         close(fd[0]);
//         if (execvp("ls", argv[0]) == -1)
//             perror("lsh");
//         //exit(EXIT_FAILURE);
//     }
//     else
//     {
//         pid=fork();
//         if (pid == 0) {
//             dup2(fd[0], 0);
//             close(fd[1]);
//             close(fd[0]);
//             if (execvp("grep", argv[1]) == -1)
//                 perror("lsh");

//         }
//         else {
//             close(fd[1]);
//             close(fd[0]);
//         wpid = waitpid(pid, &status, WUNTRACED);
//         }
//     }
//      return 1;

//}


static void redirect(int oldfd, int newfd) {
    if (oldfd != newfd) {
        dup2(oldfd, newfd);
        close(oldfd);
    }
}


void mx_pipe_rec(char ***argv, int pos, int in_fd) {
    char **prog = NULL;
    pid_t pid;

    if (argv[pos+1] == NULL) {
        redirect(in_fd, 0);
        prog = mx_strsplit(*argv[pos], '/');
        if (execvp(prog[1], argv[pos]) == -1)
            perror("lsh");
    }
    else {
        int fd[2];
        pipe(fd);
        pid = fork();
        if (pid == 0) {
            close(fd[0]);
            redirect(in_fd, 0);  /* read from in_fd */
            redirect(fd[1], 1); /* write to fd[1] */
            prog = mx_strsplit(*argv[pos], '/');
            if (execvp(prog[1], argv[pos]) == -1)
                perror("lsh");
        }
        else {
            close(fd[1]);
            close(in_fd); /* unused */
            mx_pipe_rec(argv, pos + 1, fd[0]);
        }
    }
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
    int status = 1;

    while (status) {
        printf("super_shell: ");
        line = mx_read_line();
        args = mx_strsplit(line, ' ');
        if (args != NULL) {
            status = mx_ush_execute(args);
        }
        free(line);
        free(args);
    }
}


int main() {
    //lsh_loop();

    //mx_ush_pipe_execute(); 
    char ***mas = (char ***)malloc(sizeof(char **) * 5);
    mas[0] = (char **)malloc(sizeof(char *) * 3);
    mas[1] = (char **)malloc(sizeof(char *) * 3);
    mas[2] = (char **)malloc(sizeof(char *) * 3);
    mas[3] = (char **)malloc(sizeof(char *) * 3);
    mas[4] = NULL;

   

    mas[0][0] = strdup("/bin/ls");
    mas[0][1] = strdup("-l");
    mas[0][2] = NULL;

    mas[1][0] = strdup("/bin/grep");
    mas[1][1] = strdup("c");
    mas[1][2] = NULL;

    mas[3][0] = strdup("/bin/cat");
    mas[3][1] = strdup("-e");
    mas[3][2] = NULL;

    mas[2][0] = strdup("/bin/grep");
    mas[2][1] = strdup("i");
    mas[2][2] = NULL;

    //mx_ush_pipe_execute(mas); 
    // int fd[2];
    // mx_pipe_rec(fd, 0, mas);
    mx_pipe_rec(mas, 0, 0);

}



