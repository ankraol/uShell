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

#define Close(FD) do {                                  \
    int Close_fd = (FD);                                \
    if (close(Close_fd) == -1) {                        \
      perror("close");                                  \
      fprintf(stderr, "%s:%d: close(" #FD ") %d\n",     \
              __FILE__, __LINE__, Close_fd);            \
    }                                                   \
  }while(0)

static void redirect(int oldfd, int newfd) {
    if (oldfd != newfd) {
        dup2(oldfd, newfd);
        Close(oldfd);
    }
}


void mx_pipe_rec(char ***argv, int pos, int in_fd) {
    char **prog = NULL;
    pid_t pid;
    int status; 

    if (argv[pos+1] == NULL) {
        pid = fork();
        if (pid == 0) {
        redirect(in_fd, 0);
        prog = mx_strsplit(*argv[pos], '/');
        if (execvp(prog[1], argv[pos]) == -1)
            perror("lsh");
        }
        else 
            waitpid(pid, &status, WUNTRACED);
    }
    else if (argv[pos] != NULL) {
        int fd[2];
        pipe(fd);
        pid = fork();
        if (pid == 0) {
            Close(fd[0]);
            redirect(in_fd, 0);  /* read from in_fd */
            redirect(fd[1], 1); /* write to fd[1] */
            prog = mx_strsplit(*argv[pos], '/');
            if (execvp(prog[1], argv[pos]) == -1)
                perror("lsh");
        }
        else {
            if (fd[1] != 1)
                Close(fd[1]);
            if (in_fd != 0)
                Close(in_fd); /* unused */
            mx_pipe_rec(argv, pos + 1, fd[0]);
        }
    }
}

// void mx_pipe_rec1(char ***argv, int pos, int in_fd, pid_t mypid) {
//     char **prog = NULL;
//     pid_t pid;

//     write(2, "start\n", 6);
//      write(2, mx_itoa(mypid), 300);
    

//     if (argv[pos+1] == NULL) {
//          write(2, "end\n", 6);
//          write(2, mx_itoa(in_fd), 300);
//          write(2, "\n", 2);
//          write(2, mx_itoa(mypid), 300);
//         write(2, "\n", 2);
//         write(2, mx_itoa(getpid()), 300);
//         write(2, "\n", 2);

//         redirect(in_fd, 0);
//         //dup2(in_fd, 0);
//         prog = mx_strsplit(*argv[pos], '/');
//         if (execvp(prog[1], argv[pos]) == -1)
//             perror("lsh");
//          write(2, "end\n", 6);
//          //dup2(0, in_fd);
//     }
//     else {
//         int fd[2];
//         pipe(fd);
//         pid = fork();
//         if (pid == 0) {
//             pid = fork();
//             if (pid == 0) {
                
//             Close(fd[0]);
//             redirect(in_fd, 0);  /* read from in_fd */
//             redirect(fd[1], 1); /* write to fd[1] */
//             prog = mx_strsplit(*argv[pos], '/');
//             if (execvp(prog[1], argv[pos]) == -1)
//                 perror("lsh");
//         }
//         else {
//             // Close(in_fd);
//             // if (getpid() != mypid) {
//             Close(fd[1]);
//             Close(in_fd); /* unused */
//             //}
//             //if fd[1] 
//             mx_pipe_rec(argv, pos + 1, fd[0], mypid);
//         }
//         }
//         else {
//             wait(0);
//         }

//     }
// }
// void mx_pipe_rec(char ***argv, int pos, int in_fd) {
//     pid_t pid;
//     int fd[2];
//     char **prog;
//     int status;

//     pid = fork();
//     pipe(fd);

//     if (pid == 0) {
//         if (argv[pos+1] == NULL) {
//             redirect(in_fd, 0);
//             prog = mx_strsplit(*argv[pos], '/');
//             if (execvp(prog[1], argv[pos]) == -1)
//                 perror("lsh");
//         }
//         else {
//             Close(fd[0]);
//             redirect(in_fd, 0);  /* read from in_fd */
//             redirect(fd[1], 1); /* write to fd[1] */
//             prog = mx_strsplit(*argv[pos], '/');
//             if (execvp(prog[1], argv[pos]) == -1)
//                 perror("lsh");

//             pid = fork();
//             if (pid == 0) {
//                 mx_pipe_rec(argv, pos + 1, fd[0]);
//             }
//         }
        
//     }
//     else {
//         Close(fd[1]);
//         Close(in_fd);
//         waitpid(pid, &status, WUNTRACED);
//     }

// }

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
    //char **args;
    int status = 1;

    while (status) {
        printf("super_shell: ");
       line = mx_read_line();
       // args = mx_strsplit(line, ' ');
    


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

     char ***mas_1 = (char ***)malloc(sizeof(char **) * 5);
    mas_1[0] = (char **)malloc(sizeof(char *) * 3);
    mas_1[1] = (char **)malloc(sizeof(char *) * 3);
    mas_1[2] = (char **)malloc(sizeof(char *) * 3);
    mas_1[3] = (char **)malloc(sizeof(char *) * 3);
    mas_1[4] = NULL;

   

    mas_1[0][0] = strdup("/bin/ls");
    mas_1[0][1] = strdup("-l");
    mas_1[0][2] = NULL;

    mas_1[1][0] = strdup("/bin/grep");
    mas_1[1][1] = strdup("c");
    mas_1[1][2] = NULL;

    mas_1[3][0] = strdup("/bin/cat");
    mas_1[3][1] = strdup("-e");
    mas_1[3][2] = NULL;

    mas_1[2][0] = strdup("/bin/grep");
    mas_1[2][1] = strdup("i");
    mas_1[2][2] = NULL;

    


    //mx_ush_pipe_execute(mas); 
    //int fd[2];
    //mx_pipe_rec(fd, 0, mas);
    if (status == 1)
        mx_pipe_rec(mas, 0, 0);
    else 
        mx_pipe_rec(mas_1, 0, 0);

    status++;
        // if (args != NULL) {
        //     status = mx_ush_execute(args);
        // }
        // free(line);
        // free(args);
    }
}


int main() {
    lsh_loop();

    //mx_ush_pipe_execute(); 
    // char ***mas = (char ***)malloc(sizeof(char **) * 5);
    // mas[0] = (char **)malloc(sizeof(char *) * 3);
    // mas[1] = (char **)malloc(sizeof(char *) * 3);
    // mas[2] = (char **)malloc(sizeof(char *) * 3);
    // mas[3] = (char **)malloc(sizeof(char *) * 3);
    // mas[4] = NULL;

   

    // mas[0][0] = strdup("/bin/ls");
    // mas[0][1] = strdup("-l");
    // mas[0][2] = NULL;

    // mas[1][0] = strdup("/bin/grep");
    // mas[1][1] = strdup("c");
    // mas[1][2] = NULL;

    // mas[3][0] = strdup("/bin/cat");
    // mas[3][1] = strdup("-e");
    // mas[3][2] = NULL;

    // mas[2][0] = strdup("/bin/grep");
    // mas[2][1] = strdup("i");
    // mas[2][2] = NULL;

    //mx_ush_pipe_execute(mas); 
    // int fd[2];
    // mx_pipe_rec(fd, 0, mas);
    //mx_pipe_rec(mas, 0, 0);

}



