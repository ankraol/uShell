#ifndef _HEADER_H
#define _HEADER_H

#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <errno.h>
#include <malloc/malloc.h>
#include <termios.h>
#include <stdbool.h>
#include <curses.h>
#include <term.h>
#include <limits.h>

typedef struct s_tree {
	struct s_tree *parent;
	struct s_tree *left_child;
	struct s_tree *right_child;
	char *command;
	char *operant;
} t_tree;

typedef struct s_path {
    char *file;
    char op;
    struct s_path *next;
} t_path;

typedef struct s_reddir {
    char op;
    char *task;
    t_path *input;
    t_path *output;
} t_reddir;





/*************************************************************************/


typedef struct s_cd {
    bool flag_s;
    bool flag_P;
    bool arg_min;
}               t_cd;

typedef struct s_env {
    bool flag_i;
    bool flag_P;
    bool flag_u;
}               t_env;

typedef struct s_pwd {
    bool flag_L;
    bool flag_P;
}               t_pwd;

typedef struct s_which {
    bool flag_a;
    bool flag_s;
}               t_which;

typedef struct s_echo {
    bool flag_n;
    bool flag_e;
    bool flag_E;
}               t_echo;

typedef struct s_builtin_command {
    t_cd *cd;
    t_env *env;
    t_which *which;
    t_echo *echo;
    t_pwd *pwd;
}               t_builtin_command;


typedef struct s_path_builtin {
    char *pwdP;
    char *pwdL;
    char *oldpwd;
}               t_path_builtin;


bool mx_valid_command(char **arg, int ac, t_path_builtin *pwd);
void mx_valid_flag_cd(t_builtin_command *command, char **arg, int ac, t_path_builtin *pwd, int *err);
void mx_cd_logic(char **file, t_builtin_command *command, int *err, t_path_builtin *pwd);
void mx_valid_flag_pwd(t_builtin_command *command, char **arg, int ac, int *err, t_path_builtin *pwd);


/*************************************************************************/

int main(void);
int mx_count_words(const char *str, char c);
char *mx_strnew(const int size);
char **mx_strsplit(const char *s, char c);
int mx_strlen(const char *s);
char *mx_read_env(char *file);
void mx_del_strarr(char ***arr);

char *mx_strjoin_two( char *s1,  char *s2);
char *mx_strjoin( char *s1,  char *s2);
char *mx_strcat(char *restrict s1, const char *restrict s2);

t_tree *mx_parcing(char *input);
void mx_strdel(char **str);
int mx_redirection(char *command, t_path_builtin *pwd);
int mx_pipe_rec(t_reddir *command, int pos, int in_fd, bool extInput);
int mx_ush_execute(char *argv, t_path_builtin *pwd);

char *mx_itoa(int number);

void mx_fd_change(t_reddir *command, int pos, int in_fd, bool extInput);
void mx_command_cut(char *command, int s, int f, t_reddir *tasks);
char *mx_file_to_str(const char *file);
void mx_printstr(const char *s);
t_tree **mx_works_queue(char *line);
char **mx_tokens(char *line, char sp);
int mx_strcmp(const char *s1, unsigned const char *s2);

#endif
