#ifndef _HEADER_H
#define _HEADER_H

#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

typedef struct s_tree {
	struct s_tree *parent;
	struct s_tree *left_child;
	struct s_tree *right_child;
	char *command;
	char *operant;
} t_tree;

int main(void);
void mx_parcing(char *input);
void mx_strdel(char **str);

#endif
