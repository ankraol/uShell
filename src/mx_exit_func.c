#include "header.h"

static void deleteVar(t_var **var_list) {
    t_var *p1 = *var_list;
    t_var *p2 = *var_list;

    while (p1) {
        p2 = p1->next;
        mx_strdel(&p1->name);
        mx_strdel(&p1->meaning);
        free(p1);
        p1 = p2;
    }
}

static void deleteAlias (t_alias **alias_list) {
    t_alias *p1 = *alias_list;
    t_alias *p2 = *alias_list;

    while (p1) {
        p2 = p1->next;
        mx_strdel(&p1->name);
        mx_strdel(&p1->meaning);
        free(p1);
        p1 = p2;
    }
}

static void deleteBuildstruct(t_builtin_command **my_command) {
    mx_strdel(&(*my_command)->path->pwdP);
    mx_strdel(&(*my_command)->path->pwdL);
    mx_strdel(&(*my_command)->path->oldpwd);
    free((*my_command)->path);
    free((*my_command)->cd);
    free((*my_command)->pwd);
    free((*my_command)->echo);
}

static void deleteExportArr(t_export **export_arr) {
    t_export *p1 = *export_arr;
    t_export *p2 = *export_arr;

    while (p1) {
        p2 = p1->next;
        mx_strdel(&p1->name);
        mx_strdel(&p1->value);
        free(p1);
        p1 = p2;
    }
}

void mx_exit_func(t_builtin_command *my_command) {
    deleteBuildstruct(&my_command);
    mx_delete_history(&(my_command->history));
    deleteExportArr(&(my_command->export_ar));
    deleteAlias(&(my_command->alias_list));
    deleteVar(&(my_command->var));
}
