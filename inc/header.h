#ifndef _HEADER_H
#define _HEADER_H

#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <errno.h>
#include <malloc/malloc.h>
#include <termios.h>
#include <stdbool.h>
#include <curses.h>
#include <term.h>
#include <limits.h>
#include <sys/stat.h>
#include <ctype.h>
#include <pwd.h>





/*************************************************************************/
typedef struct s_var t_var;
typedef struct s_pid_name t_pid_name;
typedef struct s_env t_env;
typedef struct s_export t_export;
typedef struct s_alias t_alias;
typedef struct s_inc t_inc;
//typedef struct s_history_name t_history_name;

extern char **environ;

struct s_inc {
    int a;
    int b;
    int c;
};

typedef struct s_history_name {
    unsigned char *name;
    int n_byte;
    int n_len;
    struct s_history_name *next;
    struct s_history_name *previous;
}                 t_history_name;

struct s_var {
    char *name;
    char *meaning;
    bool inEnv;
    struct s_var *next;
};


typedef struct s_cd {
    bool flag_s;
    bool flag_P;
    bool arg_min;
}               t_cd;

struct s_export {
    char *name;
    char *value;
    struct s_export *next;
};

typedef struct s_pwd {
    bool flag_L;
    bool flag_P;
}               t_pwd;

typedef struct s_which {
    bool flag_a;
    bool flag_s;
}               t_which;

typedef struct s_echo {
    bool flag_n;
    bool flag_e;
    bool flag_E;
}               t_echo;

typedef struct s_path_builtin {
    char *pwdP;
    char *pwdL;
    char *oldpwd;
}               t_path_builtin;

typedef struct s_builtin_command {
    t_path_builtin *path;
    t_cd *cd;
    t_env *env;
    t_which *which;
    t_echo *echo;
    t_pwd *pwd;
    t_var *var;
    t_pid_name *pid_ar;
    t_export *export_ar;
    t_alias *alias_list;
    bool unset_path;
    FILE *file;
    t_history_name *history;
    t_history_name *his;
    bool execute;
    char *path_for_ex;
}               t_builtin_command;

typedef struct s_env {
    char *name;
    struct s_env *next;
}               t_env;

typedef struct s_env_flag {
    bool flag_priority;
    bool flag_u;
    bool flag_p;
    bool i_access;
    bool be_command;
    bool find_program;
    char *pa;
    int index;
}               t_env_flag;

int mx_valid_command(char **arg, int ac, t_builtin_command *command);
void mx_valid_flag_cd(t_builtin_command *command, char **arg, int ac, int *err);
char *mx_cd_logic(char **file, t_builtin_command *command, int *err);
void mx_valid_flag_pwd(t_builtin_command *command, char **arg, int ac, int *err);
char *mx_make_logic_path(char **tmp2, char *tmp);
void mx_valid_flag_echo(t_builtin_command *command, char **arg, int ac);
void mx_change_path(char **tmp2);
char **my_strsplit(const char *s, char c);
void mx_cd_two_args(char **file, t_builtin_command *command, int *err);
bool mx_zero_arr(char **str);
void mx_change_pwd(char *tmp1, t_builtin_command *command, int *err, char **file);
int mx_str_count(char **str);

/*************************************************************************/




typedef struct s_queue t_queue;
typedef struct s_path t_path;
typedef struct s_reddir t_reddir;
typedef struct s_list t_list;
typedef struct s_alias t_alias;
typedef struct s_muteChar t_muteChar;
typedef struct s_subCom t_subCom;

struct s_subCom {
    char *com;
    char *line;
    char **origin;
};

struct s_muteChar {
    bool sQ;
    bool dQ;
    bool iSs;
};

struct s_alias {
    char *name;
    char *meaning;
    struct s_alias *next;
};

struct s_list {
    char *command;
    struct s_list *next;
};

struct s_queue {
    char *command;
    char op;
    struct s_queue *next;
};

struct s_path {
    char *file;
    char op;
    struct s_path *next;
};

struct s_reddir {
    char op;
    char *task;
    t_path *input;
    t_path *output;
};



typedef struct s_len_name {
    unsigned char ch[4];
    int n_bute;
    int n_len;
    int n_cursor;
    int cur_pos_x;
    int n_cursor_b;
    int col;
    int cursor_delta_len;
    int cursor_delta_b;
    bool first_line;
    int first_line_len;
    int first_line_byte;
    bool trig;
    bool trig_copy;
    unsigned char *buf;
}              t_len_name;

struct s_pid_name {
    int pid;
    char *name;
    int number;
    struct s_pid_name *next;
};



//int main(void);
int mx_count_words(const char *str, char c);
char *mx_strnew(const int size);
char **mx_strsplit(const char *s, char c);
int mx_strlen(const char *s);
char *mx_read_env(char *file, char *path, t_builtin_command *my_command);
void mx_del_strarr(char ***arr);

char *mx_strjoin_two( char *s1,  char *s2);
char *mx_strjoin( char *s1,  char *s2);
char *mx_strcat(char *restrict s1, const char *restrict s2);

void mx_strdel(char **str);


int mx_redirection(char *command, t_builtin_command *my_command);


int mx_pipe_rec(t_reddir *command, int pos, int in_fd, bool extInput, t_builtin_command *my_command);
int mx_ush_execute(char *argv, t_builtin_command *my_command);


char *mx_itoa(int number);

void mx_fd_change(t_reddir *command, int pos, int in_fd, bool extInput, t_builtin_command *my_command);
void mx_command_cut(char *command, int s, int f, t_reddir *tasks);
char *mx_file_to_str(const char *file);
void mx_printstr(const char *s);
t_queue **mx_works_queue(char *line);
//char **mx_tokens(char *line, char sp);
int mx_strcmp(const char *s1, unsigned const char *s2);
void mx_logicOp(char *line, t_queue **list);
char *mx_substitute(char *command, t_builtin_command *my_command);


void mx_push_back_history(t_history_name **history, unsigned char *str,
                          t_len_name *len);
void mx_delete_history(t_history_name **history);
t_len_name *mx_creat_len();
void mx_main_cycle_key(t_builtin_command *my_command, unsigned char **mystr, 
                        t_len_name *len, char *buf_first);
void mx_get_width(int *col);
void mx_one_cycle(unsigned char **mystr, t_len_name *len, unsigned char *buf,
                 FILE *file);
void mx_two_cycle(unsigned char **mystr, t_len_name *len, FILE *file);
void mx_three_cycle(unsigned char **mystr, t_len_name *len, FILE *file);
void mx_four_cycle(unsigned char **mystr, t_len_name *len, char **buf_first,
                   t_builtin_command *my_co);
void mx_byte_check_add(unsigned char *ch, int *delte_len, int *delta_byte,
                       int start);
void mx_byte_check_back(unsigned char *str, int *len, int *minus, int n);
void mx_arrow_left(unsigned char **mystr, t_len_name *len, FILE *file);
void mx_arrow_right(unsigned char **mystr, t_len_name *len, FILE *file);
void mx_arrow_up(unsigned char **mystr, t_len_name *len, char **buf_first,
                t_builtin_command *my_co);
void mx_arrow_down(unsigned char **mystr, t_len_name *len, char **buf_first,
                   t_builtin_command *my_co);
void mx_add_to_str(unsigned char **str, t_len_name **le);
char *mx_parameter_exp(char *command, t_var *varList);
void mx_aliasList(char *command, t_alias **aliasList);
char *mx_aliasSearch(char *command, t_alias *list);
void mx_back_to_str(unsigned char **str,  t_len_name **le);
void mx_delete_pid(t_pid_name **pid_list);
void mx_push_back_pid(t_pid_name **pid_list,int pid, char *name, int num);
void mx_which(char **argv, int err);
void mx_printchar(char c);
void mx_printcharerr(char c);
void mx_printerr(const char *s);
char *mx_strjoin2(char *s1, char *s2);
char *mx_strcpy(char *dst, const char *src);
bool mx_is_buildin(char *str);
char *mx_strdup(const char *s1);
void mx_fg_command(t_builtin_command *command, char **arg, int ac);
char **mx_tokenSplit(char *command);
void mx_varList(char *command, t_var **varList);
int mx_get_pid_num(t_pid_name **pid_list);
void mx_for_fg_command(t_builtin_command *command, char **arg, int ac);
void mx_wait_cont(t_pid_name **pid_ar, int n_pid);
int mx_get_peid_name(char *name, t_pid_name *pid_arr);
int mx_get_peid(int n, t_pid_name *pid_arr);
void mx_push_back_export(t_export **export_list, char *name, char *val);
void mx_delete_export(t_export **export_list);
void mx_command_export(t_builtin_command *command, char **arg, int ac);
bool mx_find_in_export(char *str, t_export **export_list, char *change);
void mx_push_back_var(t_var **var_list, char *name, char *val);
void mx_valid_flag_env(char **arg, int ac, t_builtin_command *command);
void mx_unset_command(t_builtin_command *command, int ac, char **arg);
void mx_variable_out(char *command, t_env **list);
void mx_delete_env(t_env **env_list);
void mx_push_back_env(t_env **pid_env, char *name);
int mx_ush_execute_env(char *command, t_builtin_command *my_command,
                       char **new_env, char *path);
void mx_env_two(char **arg, int ac, t_builtin_command *command);
void mx_env_one();
void mx_execute_command(t_builtin_command *command, t_env **env_list,
                        t_env_flag *env_flag, char **program);
bool mx_flag_command(char *var, int j, t_env_flag *env_flag, 
                    t_env **env_list);
bool mx_glag_p_u(t_env **env_list, t_env_flag *env_flag, char **path, 
                char *var);
char *mx_no_path(char *file, t_builtin_command *my_command);
void mx_set_signal();
int mx_count_elem(char **arr);
void mx_mistake(char *command, char ***argv, char **path, bool flag);
int mx_child(char *command, t_builtin_command *my_command, char **new_env,
             char ***argv);
void mx_del_all(char ***argv, char **path);
char *mx_nameCut(char *command, int *start);
char *mx_tokenCut(char *command, int start, int end);
bool mx_parExt(char *command);
int mx_subExec(t_builtin_command *my_command, char *line);
char *mx_subLine(char **mainCommand, char *command,
                 t_builtin_command *my_command, t_inc *index);
void mx_command_cut_four(char *command, int *arr, bool *brr, t_path **output);
bool mx_isSpace(char *command, int i);
void mx_command_cut_five(t_path **output, char *command, int *arr, int s);
void mx_command_cut_six(int *arr, char *com, t_path **output, bool *brr);
void mx_command_seven(int *arr, t_path **input);
void mx_command_eight(int *arr, t_path **output);
void mx_command_cut_ten(t_reddir *tasks, int *arr, char *com, bool *brr);
void mx_command_cut_nine(t_reddir *tasks, int *arr, int s, int f);
void mx_command_cut_eleven(t_path **output, char *command, int *arr,
                            bool *brr);
void mx_command_cut_twelve(t_path **output, char *command, int *arr,
                            bool *brr);
t_path *mx_create_list(char *command, int *i, int f, int s);
void mx_command_cut_two(char *com, int *arr, bool *brr);
void mx_quotesCheck(bool *sQ, bool *dQ, char *command, int i);
void mx_command_cut_three(t_path **output, char *command, int *arr, int s);
void mx_command_cut_one(t_reddir *tasks, int *arr, char *command,
                                bool *brr);
void mx_command_cut_thirteen(t_path **output, char *command, int *arr,
                             bool *brr);
bool mx_command_cut_fourteen( char *command, int *arr, bool *brr);
int mx_cycleOne(t_inc *index, t_muteChar *trig, char *command,
            char **line);
char *mx_parameterSearch(char *parameter, char *command);

#endif
