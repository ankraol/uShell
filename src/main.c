#include "header.h"

//Makefile has command all: install clean -> remove it

static void read_input(char **input) {
    char *c = *input;

    while ((*c++=getchar()) != '\n');
    *c = '\0';
    *input = (char *)realloc(*input, strlen(*input));
}

int main(void) {
    char *input = (char *)malloc(sizeof(char) * 1024);

    while (1) {
        printf("u$h> ");
        read_input(&input);
        mx_parcing(input);
        // printf("%s", input);
    }
}
