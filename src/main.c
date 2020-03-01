 #include "header.h"

void mx_get_twidth(int *col) {
    char *termtype = getenv("TERM");
    char *buff = malloc(2048);
    bool if_term = 0;

    if (termtype == 0) {
        termtype = strdup("xterm-256color");
        if_term = 1;
    }
    if (tgetent (buff, termtype) == 0) {
        perror("ush: ");
        exit(1);
    }
    free(buff);
    if (if_term)
        mx_strdel(&termtype);
    *col = tgetnum("co");
}

void add_to_str(unsigned char **str, unsigned char *ch, int *n, int *n_len, int *n_cursor, int *n_cursor_b) {
    int plus = 0;
    int len = 1;
    int buf_plus = 0;
    unsigned char *buf_str = NULL;

    if (ch[0] >> 7 == 0)
        plus = 1;
    if (ch[0] >> 5 == 6 && ch[1] >> 6 == 2 )
        plus = 2;
    if (ch[0] >> 4 == 14 && ch[1] >> 6 == 2 && ch[2] >> 6 == 2 )
        plus = 3;
    if (ch[0] >> 3 == 30 && ch[1] >> 6 == 2 && ch[1] >> 6 == 2 && ch[3] >> 6 == 2) {
        plus = 4;
        len = 2;
    }
    if (ch[0] >> 7 == 0 && ch[1] >> 7 == 0 && ch[2] >> 7 == 0 && ch[3] >> 7 == 0 && ch[1] != 0 && ch[2] != 0 && ch[3] != 0) {
        plus = 4;
        len = 4;
}

    if ((*n_cursor_b) == (*n)) {
        (*n) = (*n) + plus;
        (*n_cursor_b) = (*n_cursor_b) + plus;
        (*n_len) = (*n_len) + len;
        (*n_cursor) = (*n_cursor) + len;
        (*str) = (unsigned char *)realloc(*str, (*n));
        (*str)[(*n)-1] = '\0';
        buf_plus = plus;
        for (int i = 0; i < plus; i++) {
            (*str)[(*n)-1-buf_plus] = ch[i];
            buf_plus--;
        }
    }
    else {
        buf_str = (unsigned char *)malloc(sizeof(char) * ((*n) + plus));
        for (int i = 0; i < (*n_cursor_b) - 1; i++)
            buf_str[i] = (*str)[i];
        for (int i = 0; i < plus; i++)
            buf_str[(*n_cursor_b) + i - 1] = ch[i];
        for (int i = (*n_cursor_b) + plus - 1; i <= (*n); i++)
            buf_str[i] = (*str)[i - plus];
        free(*str);
        *str = buf_str;
         (*n) = (*n) + plus;
         (*n_cursor_b) = (*n_cursor_b) + plus;
         (*n_cursor) = (*n_cursor) + len;
         (*n_len) = (*n_len) + len;
    }

}

void back_to_str(unsigned char **str, int *n, int *n_len, int *n_cursor, int *n_cursor_b) {
    int minus = 0;
    int len = 1;
    unsigned char *buf_str = NULL;
    int q = 0;


    if ( (*str)[(*n)-2] >> 7 == 0)
        minus = 1;
    if ((*str)[(*n)-3] >> 5 == 6 && (*str)[(*n)-2] >> 6 == 2 )
        minus = 2;
    if ((*str)[(*n)-4] >> 4 == 14 && (*str)[(*n)-3] >> 6 == 2 && (*str)[(*n)-2] >> 6 == 2 )
        minus = 3;
    if ((*str)[(*n)-5] >> 3 == 30 && (*str)[(*n)-4] >> 6 == 2 && (*str)[(*n)-3] >> 6 == 2 && (*str)[(*n)-2] >> 6 == 2) {
        minus = 4;
        len = 2;
    }
    if ((*n_cursor_b) == (*n)) {
        if ((*n) > 1) {
            for (int i = 0; i < minus; i++) {
            (*str)[(*n) - 2 - i] = '\0';
        }
        (*n) = (*n) - minus;
        (*str) = (unsigned char *)realloc(*str, (*n));
        (*n_len) = (*n_len) - len;
        (*n_cursor) = (*n_cursor) - len;
        (*n_cursor_b) = (*n_cursor_b) - minus;
        }
    }
    else {
        if ((*n_cursor_b) > 1) {
            buf_str = (unsigned char *)malloc(sizeof(char) * ((*n) - minus));
            for (int i = 0; i < (*n_cursor_b) - minus - 1; i++)
                buf_str[i] = (*str)[i];
            q = (*n_cursor_b) - minus - 1;
            for (int i = (*n_cursor_b) - 1; i < (*n); i++) {
                buf_str[q] = (*str)[i];
                q++;
            }
            free(*str);
            *str = buf_str;
            (*n_len) = (*n_len) - len;
            (*n_cursor) = (*n_cursor) - len;
            (*n_cursor_b) = (*n_cursor_b) - minus;
            (*n) = (*n) - minus;
        }
        
    }
}


// // void add_to_str(char **str, char c, int *n) {
// //     (*n) += 1;
// //     (*str) = (char *)realloc(*str, (*n));
// //     (*str)[(*n) - 1] = '\0';
// //     (*str)[(*n) - 2] = c;
// //     //*(str[n+1]) = '\0';
// // }

unsigned char *mx_read_line(bool *trig) {
    struct termios savetty;
    struct termios tty;
    unsigned char ch[4];
    unsigned char *mystr = (unsigned char *)malloc(sizeof(char) * 1);
    int n_bute = 1;
    int n_len = 0;
     int n_cursor = 0;
     int cur_pos_x = 0;
     int n_cursor_b = 1;


    mystr[0] = '\0';
    

    tcgetattr (0, &tty);
    savetty = tty; /* Сохранить упр. информацию канонического режима */
    tty.c_lflag &= ~(ICANON | ECHO | ISIG);
    tty.c_cc[VMIN] = 1;
    tcsetattr (0, TCSAFLUSH, &tty);

    int col = 0;
    

    mx_get_twidth(&col);
    mx_printstr("u$h> ");
    

    while (1) {
        read (0, &ch, 4);
        //   fprintf(stdout, "%d--%d--%d--%d\n", ch[0], ch[1], ch[2] ,ch[3]);
        // fflush(stdout);
     
      

        // if (ch[0] == 27 && ch[1] == 91 && ch[2] == 66) // errow down
        // if (ch[0] == 27 && ch[1] == 91 && ch[2] == 65) // errow up
        // if (ch[0] == 27 && ch[1] == 91 && ch[2] == 68) // errow left
        // if (ch[0] == 27 && ch[1] == 91 && ch[2] == 67) // errow right
        //if (ch[0] == 9) //tab
    


        mx_get_twidth(&col);
        //cur_pos_x = col - ((((n_cursor + 4)/col + 1) * col) - (n_cursor + 5));
        if (ch[0] != 27 ) {
        if (n_cursor + 5  > col) {
            fprintf(stdout, "\033[%dF", (n_cursor + 4)/col);
            fflush(stdout);
            //mx_printstr("\x1b[31m");
        }
        else {
            mx_printstr("\033[1G");
        }
        mx_printstr("\033[0J");
        mx_printstr("u$h> ");

        if (ch[0] == 127 && ch[1] == 0 && ch[2] == 0 && ch[3] == 0) {
            back_to_str(&mystr, &n_bute, &n_len, &n_cursor, &n_cursor_b);
        }
       else if (ch[0] == '\n' || ch[0] == '\0') {
           if (ch[0] != '\n') 
                *trig = true;
            fprintf(stdout, "%s", mystr);
            fflush(stdout);
            write(1, "\n", 1);
            if (mx_strcmp("exit", mystr) == 0)
                exit(0);
            break;
        }
        else if (ch[0] != 27) {
            add_to_str(&mystr, ch, &n_bute, &n_len, &n_cursor, &n_cursor_b);
        }
        //fprintf(stdout, "%s", mystr);
        //fprintf(stdout, "\033[%dE", (n_cursor + 5)/col);
        //fflush(stdout);
        fprintf(stdout, "%s", mystr);
        fflush(stdout);
        // cur_pos_x = (((n_cursor + 3)/col + 1) * col) - n_cursor;
        cur_pos_x = col - ((((n_cursor + 4)/col + 1) * col) - (n_cursor + 5)) + 1;
        

         if ((((n_len + 4)/col - (n_cursor + 4)/col)) > 0) {
            // mx_printstr("ssssuka");
            fprintf(stdout, "\033[%dF", ((n_len + 4)/col - (n_cursor + 4)/col));
            fprintf(stdout, "\033[%dG", cur_pos_x);
            fflush(stdout);
        }
        else {
            fprintf(stdout, "\033[%dG", cur_pos_x);
            fflush(stdout);
        }
        }
        cur_pos_x = col - ((((n_cursor + 5)/col + 1) * col) - (n_cursor + 5)) + 1;

        
         if (ch[0] == 27 && ch[1] == 91 && ch[2] == 68) {// errow left
            if (n_cursor > 0) {
                cur_pos_x = cur_pos_x - 1;
                n_cursor = n_cursor - 1;
                n_cursor_b = n_cursor_b - 1;
                if (cur_pos_x < 1) {
                    fprintf(stdout, "\033[%dF",1);
                    fprintf(stdout, "\033[%dG", col);
                    fflush(stdout);
                    cur_pos_x = col;
                }
                else { 
                    fprintf(stdout, "\033[%dG", cur_pos_x);
                    fflush(stdout);
                }
            }
         }
         
        if (ch[0] == 27 && ch[1] == 91 && ch[2] == 67) {// errow right
            if (n_cursor < n_len) {
                cur_pos_x = cur_pos_x + 1;
                n_cursor = n_cursor + 1;
                n_cursor_b = n_cursor_b + 1;
                if (cur_pos_x > col) {
                    fprintf(stdout, "\033[%dE",1);
                    fprintf(stdout, "\033[%dG", 1);
                    fflush(stdout);
                    cur_pos_x = 1;
                }
                else {
                    fprintf(stdout, "\033[%dG", cur_pos_x);
                    fflush(stdout);
                }
            }
         }

        ch[0] = 0;
        ch[1] = 0;
        ch[2] = 0;
        ch[3] = 0;
        // fprintf(stdout, "%d--%d--%d--%d--%d\n", mystr[0], mystr[1], mystr[2] ,mystr[3], mystr[4]);
        // fflush(stdout);
        // fprintf(stdout, "%d--%d*", n_len, n_bute);
        // fflush(stdout);
    }
    // fprintf(stdout, "%d--%d--%d", (n_len+4)/col, n_len, n_bute);
    //         fflush(stdout);
    //fprintf(stdout, "%d", ((n_len + 3)/col - ((n_cursor + 3)/col)));
    //fprintf(stdout, "%d", ((n_len + 3)/col - ((n_cursor + 3)/col)));
    //fprintf(stdout, "%d--%d", n_cursor_b, n_bute);
    // fprintf(stdout, "n_len = %d, n_cursor = %d, mylen = %d, ", n_len, n_cursor, (n_len - n_cursor)/col);
    // fprintf(stdout, "mylen2 = %d", (n_len + 5)/col - (n_cursor + 5)/col);
    //fflush(stdout);
     tcsetattr (0, TCSAFLUSH, &savetty);
     return mystr;
}


void ush_loop(void) {
    unsigned char *line;
    int status = 2;
    t_queue **work = NULL;
    t_queue *p = NULL;
    bool trig = false;

    while (trig == false) {
        line = mx_read_line(&trig);
        if (line[0] != '\0') {
            work = mx_works_queue((char *)line);
            for (int i = 0; work[i]; i++) {
                p = work[i];
                for (; p; p = (*p).next) {
                    (*p).command = mx_substitute((*p).command);
                    status = mx_redirection((*p).command);
                    if (((*p).op == '&' && status == 1)
                        || ((*p).op == '|' && status == 0))
                        {
                            p = (*p).next;
                        }
                }
            }
        }
    }
}

void hdl(int sig)
{
    sig = sig +1 - 1;
    // printf("%d - pid\n", getpid());
    //printf("\n");
}

int main(void) {
    // struct sigaction act;
    // memset(&act, 0, sizeof(act));
    // act.sa_handler = hdl;
    // sigset_t set;
    // sigemptyset(&set);
    // act.sa_mask = set;
    // sigaddset(&set, SIGINT);
    // sigaddset(&set, SIGTSTP);
    

    // act.sa_mask = set;
    // sigaction(SIGINT, &act, 0);
    // sigaction(SIGTSTP, &act, 0);

    signal(SIGINT, hdl);
    signal(SIGTSTP, hdl);



    // signal(SIGTTIN, hdl);
    // signal(SIGTTOU, hdl);
    // signal(SIGQUIT, hdl);



    ush_loop();
    // lsh_loop();
    // mx_ush_pipe_execute(); 
    
}


