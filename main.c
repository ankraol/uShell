#include "header.h"

static void read_input(char **input) {
	char *c = *input;

	while ((*c++=getchar()) != '\n');
	*c = '\0';
}

int main(void) {
	char *input = NULL;

	while (1) {
		printf("u$h> ");
		read_input(&input);
		printf("%s\n", input);
	}
}
