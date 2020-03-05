#include "header.h"

int mx_str_count(char **str)  {
	int i = 0;

	while (str[i])
		i++;
	return i;
}

int mx_count_letters(const char *s, char c) {
	int i = 0;

	while (s[i] != c && s[i])
		i++;
	return i;
}


char **my_strsplit(const char *s, char c) {
	int j = 0;
	char **new;
	int count_lett;
	int i = 0;

	if (!s)
		return NULL;
	new = (char **)malloc(sizeof(char *) * (mx_count_words(s, c) + 1));
	while (s[i]) {
        if (s[i] != c) {
			count_lett = mx_count_letters(&s[i], c);
			new[j] = mx_strnew(count_lett);
			for (int k = 0; k < count_lett; k++)
				new[j][k] = s[i++];
			j++;
		}
		else
			i++;
	}
	new[j] = NULL;
	return new;
}

void mx_change_path(char **tmp2) {
	for (int i = 0; tmp2[i]; i++) { 
		if (strcmp(tmp2[i], "..") == 0) {
			memset(tmp2[i], '\0', strlen(tmp2[i]));
			for (int j = i; j > 0 ; j--) {
				if (tmp2[j][0] != 0) {
					memset(tmp2[j], '\0', strlen(tmp2[j]));
					break ;
				}
			}
		}
	}
}

void mx_fill_logic_path(char **tmp2, char *str, t_path_builtin *pwd) {
	for (int i = 0; tmp2[i]; i++) {
		if (tmp2[i][0] != '\0') {
			str = mx_strjoin(pwd->pwdL, "/");
			if (pwd->pwdL != NULL)
				mx_strdel(&pwd->pwdL);
			pwd->pwdL = mx_strjoin(str, tmp2[i]);
			mx_strdel(&str);
		}
	}
}

void mx_new_l_pwd(t_path_builtin *pwd, char **file) {
	char *tmp;
	if (strcmp(file[0], "/") == 0) {
		mx_strdel(&pwd->pwdL);
		pwd->pwdL = strdup("/");
	}
	else {
		if (file[0][0] == '/')
			tmp = strdup("/");
		else 
			tmp = mx_strjoin(pwd->pwdL, "/");
		char *tmp1 = mx_strjoin(tmp, file[0]);
		char **tmp2 = my_strsplit(tmp1, '/');
	
		mx_strdel(&tmp);
		mx_strdel(&tmp1);
		mx_change_path(tmp2);
		mx_strdel(&pwd->pwdL);
		mx_fill_logic_path(tmp2, tmp, pwd);
		mx_del_strarr(&tmp2);
	}
	//printf("pwd->pwdL == %s\n", pwd->pwdL);
}

void mx_cd_logic(char **file, t_builtin_command *command, int *err, t_path_builtin *pwd) {
	char *link_name = mx_strnew(1024);
	
	if (*err != 1) {
		if (!(command->cd->flag_P)) {
			free(pwd->oldpwd);
			pwd->oldpwd = strdup(pwd->pwdL);
		}
		mx_new_l_pwd(pwd, file);
	}

	if (readlink(file[0], link_name, 1024) >= 0) {
		if (command->cd->flag_s) {
			fprintf(stderr, "cd: not a directory: %s\n", file[0]);
			*err = 1;
		}	
	}
}
