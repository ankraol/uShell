// #include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <fcntl.h>
#include <unistd.h>
char **mx_strsplit(const char *s, char c);
char *mx_read_env(char *file);

typedef struct s_reddir {
    struct s_reddir *next;
    char *source;
    char direction;
    char *task;
} t_reddir;

static char *command_cut(char *input, int s, int f) {
    char *buf = (char *)malloc(sizeof(char) * (f - s));
    int j = 0;

    for (int i = s + 1; i <= f; i++, j++) {
        buf[j] = input[i];
    }
    buf[j] = '\0';
    return buf;
}

static t_reddir *in_out(char *command) {
    t_reddir *direct = (t_reddir *)malloc(sizeof(t_reddir));
    t_reddir *p = direct;
    int i = 0;
    int fin = 0;

    for (; command[i] != '>' && command[i] != '<'; i++);
    (*p).task = strndup(command, i);
    p->source = NULL;
    p->direction = '-';
    p->next = (t_reddir *)malloc(sizeof(t_reddir));
    p = p->next;
    for (; command[i] != '\0'; i++) {
        if (command[i] == '>' || command[i] == '<') {
            fin = i + 1;
            p->direction = command[i];
            for (; command[fin] != '>' && command[fin] != '<'
            && command[fin] != '\0'; fin++);
            p->source = command_cut(command, i, fin - 1);
            p->task = NULL;
            p->next = (t_reddir *)malloc(sizeof(t_reddir));
            p = p->next;
        }
    }
    p->source = NULL;
    p->task = NULL;
    p = NULL;
    return direct;
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

static void redirect(int oldfd, int newfd) {
    if (oldfd != newfd) {
        dup2(oldfd, newfd);
        close(oldfd);
    }
}

void mx_pars(char *line) {
    t_reddir *direct = in_out(line);
    t_reddir *p = direct->next;
    int fd;
    char **task = mx_strsplit(direct->task, ' ');
    char *path = mx_read_env(task[0]);

    for (; p->next; p = p->next) {
        if (p->direction == '>') {
            fd = open(p->source, O_WRONLY);
            redirect(fd, 1);
            if (execvp(path, task) == -1) {
                perror("lsh");
            }
        }
        else if (p->direction == '<') {
            fd = open(p->source, O_RDONLY);
            redirect(0, fd);
            if (execvp(path, task) == -1) {
                perror("lsh");
            }
        }
    }
}

static void lsh_loop() {
    char *line = NULL;

    while(1) {
        printf("u$h> ");
        line = mx_read_line();
        // printf("%s\n", line);
        mx_pars(line);
    }
}

int main() {
    lsh_loop();
    // lsh_loop();
    // mx_ush_pipe_execute(); 
    
}
