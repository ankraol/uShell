#include "header.h"

static bool mx_is_commad(char *fullname, int flags) {
    struct stat st;

    if (stat(fullname, &st) != -1) { // finded
        if ((st.st_mode & S_IXUSR) == S_IXUSR) {
            if ((flags & 2) == 2) {
                free(fullname);
                return true;
            }
            mx_printstr(fullname);
            mx_printchar('\n');
            free(fullname);
            return true;
        }
    }
    free(fullname);
    return false;
}


static int get_flags(int *i, char **argv) {
    int flags = 0;

    while(argv[++(*i)])
        if (argv[*i][0] == '-') {
            for(int j = 1; j < mx_strlen(argv[*i]); j++)
                if (argv[*i][j] == 'a')
                    flags |= 1;
                else if(argv[*i][j] == 's')
                    flags |= 2;
                else {
                    mx_printerr("which: bad option: -");
                    write(2, &argv[*i][j], 1);
                    write(2, "\n", 1);
                    return -1;
                }
        }
        else
            return flags;
    return flags;
}

/* 
1 - return true;
0 - dont return;
*/
static int check_buildin(char *command, int flags, bool *finded) {
    if (mx_is_buildin(command)) {
        if ((flags & 2) == 2) {
            printf("%s: shell built-in command\n", command);
            return 1;
        }
        printf("%s: shell built-in command\n", command);
        *finded = true;
        if ((flags & 1) == 0)
            return 1;
    }
    return 0;
}


static bool check_command(char *command, char **pathes, int flags) {
    char *fullname = 0;
    bool finded = false;

    if (check_buildin(command, flags, &finded) == 1)
        return true;
    if (command[0] == '/') {
        if (mx_is_commad(mx_strdup(command), flags))
            return true;
    }
    else {
        if (pathes == NULL)
            return false;
        for (int i = 0; pathes[i]; i++) {
            fullname = mx_strjoin_two(mx_strjoin(pathes[i], "/"), command);
            if (mx_is_commad(fullname, flags)) {
                finded = true;
            }
        }
    }
    return finded;
}

static bool check_commands(char **commands, char** pathes, int start_index,
                           int flags) {
    int i = start_index - 1;
    bool finded = false;

    while(commands[++i] != 0) {
        finded = check_command(commands[i], pathes, flags);
        if ((finded == false) && ((flags & 2) == 2))
            return false;
        if (finded == false) {
            mx_printerr(commands[i]);
            mx_printerr(" not found\n");
        }
        if (finded && ((flags & 1) == 0 || (flags & 2) == 2))
            return true;
    }
    return finded;
}

void mx_which(char **argv, int *err) {
    char **pathes = NULL;
    int i_args = 0;
    int flags = get_flags(&i_args, argv);
    int finded = false;

    if (getenv("PATH") != NULL)
        pathes = mx_strsplit(getenv("PATH"), ':');
    if (flags == -1) {
        if (pathes != NULL)
            mx_del_strarr(&pathes);
        *err = 1;
        return;
    }
    finded = check_commands(argv, pathes, i_args, flags);
    finded ? (*err = 0) : (*err = 1);
    if (pathes != NULL)
        mx_del_strarr(&pathes);
}
