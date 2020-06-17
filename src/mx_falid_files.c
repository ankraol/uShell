#include "header.h"

static void mx_swap_str(char **str1, char **str2) {
	char *tmp = *str1;
	*str1 = *str2;
	*str2 = tmp;
}

static void mx_home(t_builtin_command *command) {
    struct passwd *pw = getpwuid(getuid());

    if (command->cd->flag_P) {
        mx_strdel(&command->path->oldpwd);
        command->path->oldpwd = mx_strdup(command->path->pwdP);
    }
    else {
        mx_strdel(&command->path->oldpwd);
        command->path->oldpwd = mx_strdup(command->path->pwdL);
    }
    mx_strdel(&command->path->pwdP);
    command->path->pwdP = mx_strdup(pw->pw_dir);
    mx_strdel(&command->path->pwdL);
    command->path->pwdL = mx_strdup(pw->pw_dir);
    chdir(pw->pw_dir);
}

static void mx_print_min(char *pwd, t_builtin_command *command) {
    if (command->is_inp) {
        struct passwd *pw = getpwuid(getuid());

        if (strstr(pwd, pw->pw_dir) != NULL) {
            int len = strlen(pw->pw_dir);

            mx_printstr("~");
            mx_printstr(pwd + len);
            mx_printchar('\n');
        }
        else {
            mx_printstr(pwd);
            mx_printchar('\n');
        }
    }
}

static void mx_cd_flag_min(t_builtin_command *command) {
    chdir(command->path->oldpwd);

    mx_print_min(command->path->oldpwd, command);

    if (command->cd->flag_P) {
        mx_swap_str(&command->path->oldpwd, &command->path->pwdP);
        command->path->pwdP = getcwd(NULL, 0);
        mx_strdel(&command->path->pwdL);
        command->path->pwdL = mx_strdup(command->path->pwdP);
    }
    else {
        mx_swap_str(&command->path->oldpwd, &command->path->pwdL);
        mx_strdel(&command->path->pwdP);
        command->path->pwdP = getcwd(NULL, 0);
    }
}

void mx_falid_files(char **file, int count, t_builtin_command *com, int *err) {
    char *path = NULL;

    if (count > 2) {
        fprintf(stderr, "cd: too many arguments\n");
        *err = 1;
    }
    else if (count == 2)
        mx_cd_two_args(file, com, err);
    else if (com->cd->arg_min)
        mx_cd_flag_min(com);
    else if (!(com->cd->arg_min) && (count == 0 || strcmp(file[0], "~") == 0))
        mx_home(com);
	else {
		path = mx_cd_logic(file, com, err);
		if (path != NULL)
            mx_change_pwd(path, com, err, file);
        mx_strdel(&path);
	}
}
