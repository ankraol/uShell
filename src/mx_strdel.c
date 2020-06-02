#include "header.h"

void mx_strdel(char **str) {
    if (malloc_size(*str)){
        free(*str);
        *str = NULL;
    }
}
