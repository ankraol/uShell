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




/*************************************************************************/
typedef struct s_pid_name t_pid_name;
typedef struct s_env t_env;
typedef struct s_export t_export;

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

typedef struct s_builtin_command {
    t_cd *cd;
    t_env *env;
    t_which *which;
    t_echo *echo;
    t_pwd *pwd;
    t_pid_name *pid_ar;
    t_export *export_ar;


}               t_builtin_command;


typedef struct s_path_builtin {
    char *pwdP;
    char *pwdL;
    char *oldpwd;
}               t_path_builtin;




bool mx_valid_command(char **arg, int ac, t_path_builtin *pwd, t_builtin_command *command);
void mx_valid_flag_cd(t_builtin_command *command, char **arg, int ac,
    t_path_builtin *pwd, int *err);
void mx_cd_logic(char **file, t_builtin_command *command, int *err,
    t_path_builtin *pwd);
void mx_valid_flag_pwd(t_builtin_command *command, char **arg, int ac, int *err,
    t_path_builtin *pwd);
//char **mx_create_file(char **av, int ac, int count_files, char **file);
void mx_valid_flag_echo(t_builtin_command *command, char **arg, int ac);

/*************************************************************************/




typedef struct s_queue t_queue;
typedef struct s_path t_path;
typedef struct s_reddir t_reddir;
typedef struct s_list t_list;
typedef struct s_alias t_alias;

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

typedef struct s_history_name {
    unsigned char *name;
    int n_byte;
    int n_len;
    struct s_history_name *next;
    struct s_history_name *previous;
}               t_history_name;

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
char *mx_read_env(char *file);
void mx_del_strarr(char ***arr);

char *mx_strjoin_two( char *s1,  char *s2);
char *mx_strjoin( char *s1,  char *s2);
char *mx_strcat(char *restrict s1, const char *restrict s2);

void mx_strdel(char **str);

int mx_redirection(char *command, t_path_builtin *pwd, t_builtin_command *my_command, t_alias **aliasList);
int mx_pipe_rec(t_reddir *command, int pos, int in_fd, bool extInput);
int mx_ush_execute(char *argv, t_path_builtin *pwd, t_builtin_command *my_command);


char *mx_itoa(int number);

void mx_fd_change(t_reddir *command, int pos, int in_fd, bool extInput);
void mx_command_cut(char *command, int s, int f, t_reddir *tasks);
char *mx_file_to_str(const char *file);
void mx_printstr(const char *s);
t_queue **mx_works_queue(char *line);
char **mx_tokens(char *line, char sp);
int mx_strcmp(const char *s1, unsigned const char *s2);
void mx_logicOp(char *line, t_queue **list);

char *mx_substitute(char *command,t_path_builtin *pwd, t_builtin_command *my_command, t_alias **aliasList);

void mx_push_back_history(t_history_name **history, unsigned char *str,
                          t_len_name *len);
void mx_delete_history(t_history_name **history);
t_len_name *mx_creat_len();
void mx_main_cycle_key(t_history_name **history, unsigned char **mystr, 
                        t_len_name *len, char *buf_first);
void mx_get_width(int *col);
void mx_one_cycle(unsigned char **mystr, t_len_name *len, unsigned char *buf);
void mx_two_cycle(unsigned char **mystr, t_len_name *len);
void mx_three_cycle(unsigned char **mystr, t_len_name *len);
void mx_four_cycle(unsigned char **mystr, t_len_name *len, char **buf_first,
                   t_history_name **his);
void mx_byte_check_add(unsigned char *ch, int *delte_len, int *delta_byte,
                       int start);
void mx_byte_check_back(unsigned char *str, int *len, int *minus, int n);
void mx_arrow_left(unsigned char **mystr, t_len_name *len);
void mx_arrow_right(unsigned char **mystr, t_len_name *len);
void mx_arrow_up(unsigned char **mystr, t_len_name *len, char **buf_first,
                 t_history_name **his);
void mx_arrow_down(unsigned char **mystr, t_len_name *len, char **buf_first,
                   t_history_name **his);
void mx_add_to_str(unsigned char **str, t_len_name **le);
char *mx_parameter_exp(char *command);
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
int mx_get_pid_num(t_pid_name **pid_list);
void mx_for_fg_command(t_builtin_command *command, char **arg, int ac);
void mx_wait_cont(t_pid_name **pid_ar, int n_pid);
int mx_get_peid_name(char *name, t_pid_name *pid_arr);
int mx_get_peid(int n, t_pid_name *pid_arr);
void mx_push_back_export(t_export **export_list, char *name, char *val);
void mx_delete_export(t_export **export_list);
void mx_command_export(t_builtin_command *command, char **arg, int ac);

#endif
