#include "header.h"

// void mx_get_twidth(int *col) {
//     char *termtype = getenv("TERM");
//     char *buff = malloc(2048);
//     bool if_term = 0;

//     if (termtype == 0) {
//         termtype = strdup("xterm-256color");
//         if_term = 1;
//     }
//     if (tgetent (buff, termtype) == 0) {
//         perror("ush: ");
//         exit(1);
//     }
//     free(buff);
//     if (if_term)
//         mx_strdel(&termtype);
//     *col = tgetnum("co");
// }

// void mx_byte_check_add(unsigned char *ch, int *delte_len, int *delta_byte,
//                        int start) {
//     if (ch[start] >> 7 == 0)
//         *delta_byte = 1;
//     if (ch[start] >> 5 == 6 && ch[start + 1] >> 6 == 2 )
//         *delta_byte = 2;
//     if (ch[start] >> 4 == 14 && ch[start + 1] >> 6 == 2
//         && ch[start + 2] >> 6 == 2 )
//         *delta_byte = 3;
//     if (ch[start] >> 3 == 30 && ch[start + 1] >> 6 == 2 
//         && ch[start + 2] >> 6 == 2 && ch[start + 3] >> 6 == 2) {
//         *delta_byte = 4;
//         *delte_len = 2;
//     }
// }

// void mx_byte_check_back(unsigned char *str, int *len, int *minus, int n) {
//     if ( str[n-2] >> 7 == 0)
//         *minus = 1;
//     if (str[n-3] >> 5 == 6 && str[n-2] >> 6 == 2 )
//         *minus = 2;
//     if (str[n-4] >> 4 == 14 && str[n-3] >> 6 == 2 && str[n-2] >> 6 == 2 )
//         *minus = 3;
//     if (str[n-5] >> 3 == 30 && str[n-4] >> 6 == 2 && str[n-3] >> 6 == 2
//         && str[n-2] >> 6 == 2) {
//         *minus = 4;
//         *len = 2;
//     }
// }



// void add_to_str(unsigned char **str, unsigned char *ch, int *n, int *n_len, int *n_cursor, int *n_cursor_b) {
//     int plus = 0;
//     int len = 1;
//     int buf_plus = 0;
//     unsigned char *buf_str = NULL;

//     mx_byte_check_add(ch, &len, &plus, 0);
//     if (ch[0] >> 7 == 0 && ch[1] >> 7 == 0 && ch[2] >> 7 == 0 && ch[3] >> 7 == 0 && ch[1] != 0 && ch[2] != 0 && ch[3] != 0) {
//         plus = 4;
//         len = 4;
// }

//     if ((*n_cursor_b) == (*n)) {
//         (*n) = (*n) + plus;
//         (*n_cursor_b) = (*n_cursor_b) + plus;
//         (*n_len) = (*n_len) + len;
//         (*n_cursor) = (*n_cursor) + len;
//         (*str) = (unsigned char *)realloc(*str, (*n));
//         (*str)[(*n)-1] = '\0';
//         buf_plus = plus;
//         for (int i = 0; i < plus; i++) {
//             (*str)[(*n)-1-buf_plus] = ch[i];
//             buf_plus--;
//         }
//     }
//     else {
//         buf_str = (unsigned char *)malloc(sizeof(char) * ((*n) + plus));
//         for (int i = 0; i < (*n_cursor_b) - 1; i++)
//             buf_str[i] = (*str)[i];
//         for (int i = 0; i < plus; i++)
//             buf_str[(*n_cursor_b) + i - 1] = ch[i];
//         for (int i = (*n_cursor_b) + plus - 1; i <= (*n); i++)
//             buf_str[i] = (*str)[i - plus];
//         free(*str);
//         *str = buf_str;
//          (*n) = (*n) + plus;
//          (*n_cursor_b) = (*n_cursor_b) + plus;
//          (*n_cursor) = (*n_cursor) + len;
//          (*n_len) = (*n_len) + len;
//     }

// }

// void back_to_str(unsigned char **str, int *n, int *n_len, int *n_cursor, int *n_cursor_b) {
//     int minus = 0;
//     int len = 1;
//     unsigned char *buf_str = NULL;
//     int q = 0;

//     mx_byte_check_back(*str, &len, &minus, *n);
//     if ((*n_cursor_b) == (*n)) {
//         if ((*n) > 1) {
//             for (int i = 0; i < minus; i++) {
//             (*str)[(*n) - 2 - i] = '\0';
//         }
//         (*n) = (*n) - minus;
//         (*str) = (unsigned char *)realloc(*str, (*n));
//         (*n_len) = (*n_len) - len;
//         (*n_cursor) = (*n_cursor) - len;
//         (*n_cursor_b) = (*n_cursor_b) - minus;
//         }
//     }
//     else {
//         if ((*n_cursor_b) > 1) {
//             buf_str = (unsigned char *)malloc(sizeof(char) * ((*n) - minus));
//             for (int i = 0; i < (*n_cursor_b) - minus - 1; i++)
//                 buf_str[i] = (*str)[i];
//             q = (*n_cursor_b) - minus - 1;
//             for (int i = (*n_cursor_b) - 1; i < (*n); i++) {
//                 buf_str[q] = (*str)[i];
//                 q++;
//             }
//             free(*str);
//             *str = buf_str;
//             (*n_len) = (*n_len) - len;
//             (*n_cursor) = (*n_cursor) - len;
//             (*n_cursor_b) = (*n_cursor_b) - minus;
//             (*n) = (*n) - minus;
//         }
        
//     }
// }


// unsigned char *mx_read_line(bool *trig, t_history_name **history) {
//     struct termios savetty;
//     struct termios tty;
//     t_len_name *len = mx_creat_len();


//     // unsigned char ch[4];
//     // unsigned char *mystr = (unsigned char *)malloc(sizeof(char) * 1);
//     // int n_bute = 1;
//     // int n_len = 0;
//     // int n_cursor = 0;
//     // int cur_pos_x = 0;
//     // int n_cursor_b = 1;
//     // int col = 0;
//     // int cursor_delta_len = 1;
//     // int cursor_delta_b = 0;

//     // bool first_line = true;
//     // char *buf_first = NULL;
//     // int first_line_len = 0;
//     // int first_line_byte = 1;
//     // mystr[0] = '\0';


//     tcgetattr (0, &tty);
//     savetty = tty;
//     tty.c_lflag &= ~(ICANON | ECHO | ISIG);
//     tty.c_cc[VMIN] = 1;
//     tcsetattr (0, TCSAFLUSH, &tty);
//     mx_get_twidth(len->col);
//     mx_printstr("u$h> ");
    

//     while (1) {
//         read (0, len->ch, 4);
//         mx_get_twidth(len->col);
//         if (len->ch[0] != 27 && len->ch[0] != 9 ) {
//             if (len->n_cursor + 5  > len->col) {
//                 fprintf(stdout, "\033[%dF", (len->n_cursor + 4)/len->col);
//                 fflush(stdout);
//             }
//             else {
//                 mx_printstr("\033[1G");
//             }
//             mx_printstr("\033[0J");
//             mx_printstr("u$h> ");

//             if (len->ch[0] == 127 && len->ch[1] == 0 && len->ch[2] == 0 && len->ch[3] == 0) {
//                 back_to_str(len->mystr, &n_bute, &n_len, &n_cursor, &n_cursor_b);
//             }
//         else if (ch[0] == '\n' || ch[0] == '\0') {
//             if (ch[0] != '\n') 
//                     *trig = true;
//                 fprintf(stdout, "%s", mystr);
//                 fflush(stdout);
//                 write(1, "\n", 1);
//                 if (mx_strcmp("exit", mystr) == 0) {
//                     if (malloc_size(buf_first))
//                         free(buf_first);
//                     if (malloc_size(mystr))
//                         free(mystr);
//                     mx_delete_history(history);
//                     exit(0);
//                 }
                    
//                 break;
//             }
//             else if (ch[0] != 27) {
//                 add_to_str(&mystr, ch, &n_bute, &n_len, &n_cursor, &n_cursor_b);
//             }
//             fprintf(stdout, "%s", mystr);
//             fflush(stdout);
//             cur_pos_x = col - ((((n_cursor + 4)/col + 1) * col) - (n_cursor + 5)) + 1;
            

//             if ((((n_len + 4)/col - (n_cursor + 4)/col)) > 0) {
//                 fprintf(stdout, "\033[%dF", ((n_len + 4)/col - (n_cursor + 4)/col));
//                 fprintf(stdout, "\033[%dG", cur_pos_x);
//                 fflush(stdout);
//             }
//             else {
//                 fprintf(stdout, "\033[%dG", cur_pos_x);
//                 fflush(stdout);
//             }
//         }
//         cur_pos_x = col - ((((n_cursor + 5)/col + 1) * col) - (n_cursor + 5)) + 1;

        
//          if (ch[0] == 27 && ch[1] == 91 && ch[2] == 68) {// errow left
//             if (n_cursor > 0) {
//                 mx_byte_check_back(mystr, &cursor_delta_len, &cursor_delta_b, n_cursor_b);
//                 cur_pos_x = cur_pos_x - cursor_delta_len;
//                 n_cursor = n_cursor - cursor_delta_len;
//                 n_cursor_b = n_cursor_b - cursor_delta_b;
//                 cursor_delta_len = 1;
//                 if (cur_pos_x < 1) {
//                     fprintf(stdout, "\033[%dF",1);
//                     fprintf(stdout, "\033[%dG", col);
//                     fflush(stdout);
//                     cur_pos_x = col;
//                 }
//                 else { 
//                     fprintf(stdout, "\033[%dG", cur_pos_x);
//                     fflush(stdout);
//                 }
//             }
//          }
        
//         if (ch[0] == 27 && ch[1] == 91 && ch[2] == 67) {// errow right
//             if (n_cursor < n_len) {
//                 mx_byte_check_add(mystr, &cursor_delta_len, &cursor_delta_b, n_cursor_b);
//                 cur_pos_x = cur_pos_x + cursor_delta_len;
//                 n_cursor = n_cursor + cursor_delta_len;
//                 n_cursor_b = n_cursor_b + cursor_delta_b;
//                 cursor_delta_len = 1;
//                 if (cur_pos_x > col) {
//                     fprintf(stdout, "\033[%dE",1);
//                     fprintf(stdout, "\033[%dG", 1);
//                     fflush(stdout);
//                     cur_pos_x = 1;
//                 }
//                 else {
//                     fprintf(stdout, "\033[%dG", cur_pos_x);
//                     fflush(stdout);
//                 }
//             }
//          }
//          if (ch[0] == 27 && ch[1] == 91 && ch[2] == 65) {// errow up
//             if (*history != NULL) {
//                 if (first_line == true) {
//                     first_line_len = n_len;
//                     first_line_byte = n_bute;
//                     buf_first = strdup((char *) mystr);
//                     free(mystr);
//                     first_line = false;
//                 }
//                 if (n_cursor + 5 > col) {
//                     fprintf(stdout, "\033[%dF", (n_cursor + 4)/col);
//                     fflush(stdout);
//                 }
//                 else {
//                     mx_printstr("\033[1G");
//                     }
//                 mx_printstr("\033[0J");
//                 mx_printstr("u$h> ");
//                 n_cursor =(*history)->n_len;
//                 n_cursor_b = (*history)->n_byte;
//                 n_len = n_cursor;
//                 n_bute = n_cursor_b;
//                 mystr = (*history)->name;
//                 fprintf(stdout, "%s", (*history)->name);
//                 fflush(stdout);
//                 if ((*history)->next)
//                     (*history) = (*history)->next;
//            }
//          }
//         if (ch[0] == 27 && ch[1] == 91 && ch[2] == 66) { // errow down
//                 if ((*history)->previous != NULL || first_line == false) {
                    
//                 if (n_cursor + 5 > col) {
//                     fprintf(stdout, "\033[%dF", (n_cursor + 4)/col);
//                     fflush(stdout);
//                 }
//                 else {
//                     mx_printstr("\033[1G");
//                     }
//                 mx_printstr("\033[0J");
//                 mx_printstr("u$h> ");
//                 if ((*history)->previous != NULL) {
//                     (*history) = (*history)->previous;
//                     n_cursor =(*history)->n_len;
//                     n_cursor_b = (*history)->n_byte;
//                     n_len = n_cursor;
//                     n_bute = n_cursor_b;
//                     mystr = (*history)->name;
//                     fprintf(stdout, "%s", (*history)->name);
//                     fflush(stdout);
//                 }
//                 else {
//                     if (first_line == false) {
//                         n_cursor = first_line_len;
//                         n_cursor_b = first_line_byte;
//                         n_len = first_line_len;
//                         n_bute = n_cursor_b;
//                         mystr = (unsigned char *) buf_first;
//                         fprintf(stdout, "%s", mystr);
//                         fflush(stdout);
//                         first_line = true;
//                         first_line_len = 0;
//                         first_line_byte = 1;
//                     }
//                 }
//             }
//         }
//         ch[0] = 0;
//         ch[1] = 0;
//         ch[2] = 0;
//         ch[3] = 0;
//     }

//     if (first_line != true)
//         free(buf_first);
//     if (mystr[0] == '\n')
//         free(mystr);
//     else 
//         mx_push_back_history(history, mystr, n_bute, n_len);
//     tcsetattr (0, TCSAFLUSH, &savetty);
//     return mystr;
// }


// void ush_loop(void) {
//     unsigned char *line;
//     //int status = 2;
//     //t_queue **work = NULL;
//     //t_queue *p = NULL;
//     bool trig = false;
//     t_history_name *history = NULL;

//     while (trig == false) {
//         //mx_printstr("u$h> ");
//         line = mx_read_line(&trig, &history);
//         // if (line[0] != '\0') {
//         //     work = mx_works_queue((char *)line);
//         //     for (int i = 0; work[i]; i++) {
//         //         p = work[i];
//         //         for (; p; p = (*p).next) {
//         //             (*p).command = mx_substitute((*p).command);
//         //             status = mx_redirection((*p).command);
//         //             if (((*p).op == '&' && status == 1)
//         //                 || ((*p).op == '|' && status == 0))
//         //                 {
//         //                     p = (*p).next;
//         //                 }
//         //         }
//         //     }
//         // }
//     }
// }

// void hdl(int sig)
// {
//     sig = sig +1 - 1;
//     // printf("%d - pid\n", getpid());
//     //printf("\n");
// }

// int main(void) {
//     // struct sigaction act;
//     // memset(&act, 0, sizeof(act));
//     // act.sa_handler = hdl;
//     // sigset_t set;
//     // sigemptyset(&set);
//     // act.sa_mask = set;
//     // sigaddset(&set, SIGINT);
//     // sigaddset(&set, SIGTSTP);
    

//     // act.sa_mask = set;
//     // sigaction(SIGINT, &act, 0);
//     // sigaction(SIGTSTP, &act, 0);

//     signal(SIGINT, hdl);
//     signal(SIGTSTP, hdl);



//     // signal(SIGTTIN, hdl);
//     // signal(SIGTTOU, hdl);
//     // signal(SIGQUIT, hdl);

//     ush_loop();
//     //system("leaks -q ush");
//     // lsh_loop();
//     // mx_ush_pipe_execute(); 



static void quotesCheck(bool *sQ, bool *dQ, char *command, int i) {
    if (command[i] == 34 && command[i - 1] != 92 && (*sQ) == false) {
        if ((*dQ) == false)
            *dQ = true;
        else
            *dQ = false;
    }
    else if (command[i] == 39 && (*dQ) == false) {
        if ((*sQ) == false)
            *sQ = true;
        else
            *sQ = false;
    }
}

static bool isSpace(char *command, int i) {
    if (command[i] == ' ' && command[i - 1] != 92)
        return true;
    else if (command[i] == 92 && command[i - 1] != 92)
        return true;
    else if (command[i] == 34 && command[i - 1] != 92)
        return true;
    else if (command[i] == 39 && command[i - 1] != 92)
        return true;
    else if (command[i] == 36 && command[i - 1] != 92)
        return true;
    else if ((command[i] == 125 || command[i] == 123) && command[i - 1] != 92)
        return true;
    else if ((command[i] == 40 || command[i] == 41) && command[i - 1] != 92)
        return true;
    else
        return false;
}

t_path *create_list(char *command, int *i, int f, int s) {
    t_path *p = NULL;
    int j = 0;
    // bool iSbl = false;
    // bool iSesc = false;

    p = (t_path *)malloc(sizeof(t_path));
    p->op = command[(*i)];
    for ((*i) += 1; command[(*i)] == ' '; (*i)++);
    p->file = (char *)malloc(sizeof(char) * (f - s));
    while ((*i) < f && command[(*i) + 1] != '<' && command[(*i) + 1] != '>') {
        if (isSpace(command, (*i)) == false) {
            // printf("let it in -> %c\n", command[(*i)]);
            p->file[j] = command[(*i)];
            (*i)++;
            j++;
        }
        else {
            (*i)++;
        }
    }
    p->file[j] = '\0';
    p->file = realloc(p->file, strlen(p->file));
    // printf("INPUT = %s\n", p->file);
    p->next = NULL;
    return p;
}

void mx_command_cut2(char *command, int s, int f, t_reddir *tasks) {
    t_path **output = NULL;
    t_path **input = NULL;
    int i = s;
    int q = 0;
    int j = 0;
    bool iSdq = false;
    bool iSsq = false;

    tasks->task = (char *)malloc(sizeof(char) * (f - s));
    tasks->input = NULL;
    tasks->output = NULL;
    input = &tasks->input;
    output = &tasks->output;
    for (; i < f; i++) {
        quotesCheck(&iSsq, &iSdq, command, i);
        if (((command[i] == '>' || command[i] == '<')
            && iSdq == false && iSsq == false) || command[i] == '\0')
            {
                break;
            }
            else if (command[i] == ' ' && (command[i + 1] == '>' || command[i + 1] == '<')
                && iSdq == false && iSsq == false)
                {
                    break;
                }
            else {
                tasks->task[q] = command[i];
                q++;
            }
    }
    tasks->task[q] = '\0';
    tasks->task = realloc(tasks->task, strlen(tasks->task) + 1);
    printf("inside command cut 2 = %s\n", tasks->task);

        for (; i < f; i++) {
            printf("ja tut\n");
            if (command[i] == 34 && command[i - 1] != 92 && iSsq == false) {
                if (iSdq == false)
                    iSdq = true;
                else
                    iSdq = false;
            }
            else if (command[i] == 39 && iSdq == false) {
                if (iSsq == false)
                    iSsq = true;
                else
                    iSsq = false;
            }
            if (command[i] == '>'&& i < f && iSdq == false && iSsq == false) {
                if (!(*output)) {
                    *output = create_list(command, &i, f, s);
                }
                else {
                    for(; (*output)->next; output = &(*output)->next);
                    (*output)->next = (t_path *)malloc(sizeof(t_path));
                    (*output)->next->op = command[i];
                    for (i += 1; command[i] == ' '; i++);
                    (*output)->next->file = (char *)malloc(sizeof(char) * (f - s));
                    for (j = 0; i < f;) {
                        if (command[i] == 34 && command[i - 1] != 92 && iSsq == false) {
                            if (iSdq == false)
                                iSdq = true;
                            else
                                iSdq = false;
                        }
                        else if (command[i] == 39 && iSdq == false) {
                            if (iSsq == false)
                                iSsq = true;
                            else
                                iSsq = false;
                        }
                        if (iSsq == false && iSdq == false){
                            if (isSpace(command, i) == false){
                                (*output)->next->file[j] = command[i];
                                i++;
                                j++;
                            }
                            else
                                i++;
                        }
                        else if (iSsq == true || iSdq == true) {
                            (*output)->next->file[j] = command[i];
                            i++;
                            j++;
                        }
                        else if ((command[i] == '<' || command[i] == '>') && iSsq == false && iSdq == false)
                            break;
                    }
                    (*output)->next->file[j] = '\0';
                    (*output)->next->file = realloc((*output)->next->file, strlen((*output)->next->file) + 1);
                    (*output)->next->next = NULL;
                }
            }
            if (command[i] == '<' && i < f && iSsq == false && iSdq == false) {
                if (!(*input)) {
                    *input = create_list(command, &i, f, s);
                }
                else {
                    for(; (*output)->next; output = &(*output)->next);
                    (*output)->next = (t_path *)malloc(sizeof(t_path));
                    (*output)->next->op = command[i];
                    for (i += 1; command[i] == ' '; i++);
                    (*output)->next->file = (char *)malloc(sizeof(char) * (f - s));
                    for (j = 0; i < f;) {
                        if (command[i] == 34 && command[i - 1] != 92 && iSsq == false) {
                            if (iSdq == false)
                                iSdq = true;
                            else
                                iSdq = false;
                        }
                        else if (command[i] == 39 && iSdq == false) {
                            if (iSsq == false)
                                iSsq = true;
                            else
                                iSsq = false;
                        }
                        if (iSsq == false && iSdq == false){
                            if (isSpace(command, i) == false){
                                (*output)->next->file[j] = command[i];
                                i++;
                                j++;
                            }
                            else
                                i++;
                        }
                        else if (iSsq == true || iSdq == true) {
                            (*output)->next->file[j] = command[i];
                            i++;
                            j++;
                        }
                        else if ((command[i] == '<' || command[i] == '>') && iSsq == false && iSdq == false)
                            break;
                        }
                        (*input)->next->file[j] = '\0';
                        (*input)->next->file = realloc((*input)->next->file, strlen((*input)->next->file) + 1);
                        (*input)->next->next = NULL;
                }
            }
        }
        printf("at the end of command cut 2 = %s\n", tasks->task);
}
