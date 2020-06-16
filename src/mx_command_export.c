#include "header.h"

static void sort_list(t_export **lst) {
	t_export *buf = NULL;
	t_export *buft = NULL;
	char *tmp_name = NULL;
    char *tmp_val = NULL;

	for (buft = *lst; buft != NULL; buft = buft->next) {
		for (buf = buft->next; buf != NULL; buf = buf->next) { 
			if (strcmp(buf->name, buft->name) < 0) {
				tmp_name = buft->name;
                tmp_val = buft->value;
				buft->name = buf->name;
				buf->name = tmp_name;
                buft->value = buf->value;
				buf->value = tmp_val;
			}
		}
	}
}

static void print_list(t_export *export_list) {
 
    while (export_list) {
        printf("%s=%s\n", export_list->name, export_list->value);
        export_list = export_list->next;
    }
}

static int check_str(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '?' || str[i] == '*') {
            mx_printerr("ush: no matches found: ");
            mx_printerr(str);
            mx_printerr("\n");
            return 2;
        }
        if (!isalpha(str[i]) && str[i] != '_' && !isdigit(str[i])) {
            mx_printerr("export: not valid in this context ");
            mx_printerr(str);
            mx_printerr("\n");
            return 1;
        }
        if (i == 0 && isdigit(str[i])) {
            mx_printerr("export: not an identifier: ");
            mx_printerr(str);
            mx_printerr("\n");
            return 3;
        }
    }
    return 0;
}

static bool find_in_var(char *str, t_var **varList, char *change){
    while(*varList) {
        if (strcmp((*varList)->name, str) == 0) {
            if (change != NULL) {
                free((*varList)->meaning);
                (*varList)->meaning = strdup(change);
            }
            return true;
        }
        *varList = (*varList)->next;
    }
    return false;
}

static void general(t_builtin_command *command, char **arr_val) {
    if (arr_val[1] != NULL) {
        if (find_in_var(arr_val[0], &command->var, arr_val[1]) == false)
            mx_push_back_var(&command->var, arr_val[0], arr_val[1]);
        if (!mx_find_in_export(arr_val[0], &command->export_ar, arr_val[1]))
            mx_push_back_export(&command->export_ar, arr_val[0], arr_val[1]);
        setenv(arr_val[0], arr_val[1], 1);
    }
    else {
        if (find_in_var(arr_val[0], &command->var, NULL) == false)
            mx_push_back_export(&command->export_ar, arr_val[0], "''");
        else {
            mx_push_back_export(&command->export_ar,
                                arr_val[0], command->var->meaning);
            setenv(arr_val[0], command->var->meaning, 1);
        }
    }
    mx_del_export_var(&command->var);
}

bool mx_rovno(char *str) {
    for (int i = 0; str[i]; i++) {
        if (str[i] == '=')
            return true;
    }
    return false;
}

void mx_command_export(t_builtin_command *com, char **arg, int ac, int *err) {
    char **arr_val;

    if (ac == 1) {
        sort_list(&com->export_ar);
        print_list(com->export_ar);
    }
    else {
        for (int i = 1; i < ac; i++)
        {
            if (mx_rovno(arg[i])) {
                arr_val = mx_strsplit(arg[i], '='); 
                if (check_str(arr_val[0]) == 0) {
                       general(com, arr_val);
                }
                else
                    *err = 1;
                mx_del_strarr(&arr_val);
            }
        }
    }
}
