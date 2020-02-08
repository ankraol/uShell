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



typedef struct s_tree {
	struct s_tree *parent;
	struct s_tree *left_child;
	struct s_tree *right_child;
	char *command;
	char *operant;
} t_tree;

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
<<<<<<< HEAD
char *mx_itoa(int number);
=======
void mx_redirection(char *command);
>>>>>>> 91f073c47397ad27986c917b75e2198ec4f871fd

#endif
