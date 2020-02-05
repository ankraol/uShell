#include "header.h"

static char *read_input() {
	char *c = *input;

	while ((*c++=getchar()) != '\n');
	*c = '\0';
}

int main(void) {
	char *input = NULL;

	while (1) {
		printf("u$h> ");
		input = read_input();
		printf("%s\n", input);
	}
}
