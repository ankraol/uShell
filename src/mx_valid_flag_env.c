#include "header.h"

void mx_valid_flag_env(char **arg, int ac) {
    extern char **environ;
    char **full_val = NULL;

    if (ac == 1 && environ != NULL) {
        for (int i = 0; environ[i] != NULL; i++) {
            full_val = mx_strsplit(environ[i], '=');
            printf("%s=%s\n", full_val[0], full_val[1]);
            mx_del_strarr(&full_val);
        }
    }
    else {
        arg = NULL;
    }
}
