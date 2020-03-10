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
    while (export_list)
    {
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

static void find_in_var(char *str, t_var *varList){
    while(varList) {
        if (strcmp(varList->name, str) == 0) {
            printf("SUCCCCCKKKK\n");
            return;
        }
        varList = varList->next;
    }
}

void mx_command_export(t_builtin_command *command, char **arg, int ac) {
    char **arr_val;

    if (ac == 1) {
        sort_list(&command->export_ar);
        print_list(command->export_ar);
    }
    else {
        for (int i = 1; i < ac; i++)
        {
            arr_val = mx_strsplit(arg[i], '=');
            //printf("VAL = %s\n", arr_val[0]);
            if (check_str(arr_val[0]) == 0) {
                if(arr_val[1] != NULL) {
                    //check in the var_list and delete
                    find_in_var(arr_val[0], command->var);
                    //check in the list if this val is already created
                    mx_push_back_export(&command->export_ar, arr_val[0], arr_val[1]);
                    //add to env
                }
                else {
                    //check in val_list
                    //if no - add_to_export
                    // if yes add_to export and env
                }
            } 
        }
    }
}
