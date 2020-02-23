 #include "header.h"

#include <stdlib.h>

// char *mx_read_line() {
//     char c;
//     int bufsize = 1024;
//     int position = 0;
//     char *buffer = (char *)malloc(sizeof(char) * bufsize);

//     while(1) {
//         c = getchar();
//         if (c == '\0' || c == '\n') {
//             buffer[position] = '\0';
//             return buffer;
//         }
//         else {
//             buffer[position] = c;
//         }
//         position++;
//     }
// }

void mx_get_twidth(int *col, int *line) {
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
    *line = tgetnum("li");
}

void add_to_str(char **str, char c, int *n, int *len_line) {
    (*n) += 1;
    (*len_line)++;
    (*str) = (char *)realloc(*str, (*n));
    (*str)[(*n) - 1] = '\0';
    (*str)[(*n) - 2] = c;
    //*(str[n+1]) = '\0';
}

void back_to_str(char **str, int *n, int *len_line) {
    if ((*n) > 1) {
        (*str)[(*n) - 2] = '\0';
        (*n) -= 1;
        (*len_line)--;
        (*str) = (char *)realloc(*str, (*n));
    }
}

// void add_to_str(char **str, char c, int *n) {
//     (*n) += 1;
//     (*str) = (char *)realloc(*str, (*n));
//     (*str)[(*n) - 1] = '\0';
//     (*str)[(*n) - 2] = c;
//     //*(str[n+1]) = '\0';
// }

// void back_to_str(char **str, int *n) {
//     if ((*n) > 1) {
//         (*str)[(*n) - 2] = '\0';
//         (*n) -= 1;
//         (*str) = (char *)realloc(*str, (*n));
//     }
// }


char *mx_read_line() {
    struct termios savetty;
    struct termios tty;
    char ch = 0;
    char *mystr = (char *)malloc(sizeof(char) * 1);
    mystr[0] = '\0';
    char *line = (char *)malloc(sizeof(char) * 1);
    line[0] = '\0';
    int n = 1;
    

    tcgetattr (0, &tty);
    savetty = tty; /* Сохранить упр. информацию канонического режима */
    tty.c_lflag &= ~(ICANON | ECHO | ISIG);
    tty.c_cc[VMIN] = 1;
    tcsetattr (0, TCSAFLUSH, &tty);

    // int x = 1;
    // int y = 1;
    int col = 0;
    int lin = 0;
    int start_x = 0;
    int start_y = 0;
     mx_get_twidth(&col, &lin);


    mx_printstr("\033[6n");

    //scanf("\033[%d;%dR", &start_x, &start_y);

    
    //mx_printstr("\0337");
    scanf("\033[%d;%dR", &start_x, &start_y);

    int len_str = 0;
    if (lin != start_x)
        len_str = (((lin+1) - start_x) * col ) - 5;
    else 
        len_str =  col - 5;
    // fprintf(stdout, "--%d--", len_str);
    // fflush(stdout);

//   fprintf(stdout, "line = %d, col = %d, len_line = %d", lin, col, len_str );
//        fflush(stdout);
    mx_printstr("u$h> ");
    // scanf("\033[%d;%df", &start_x, &start_y);
    // mx_printstr("\033[6n");

    //scanf("\033[%d;%dR", &start_x, &start_y);
    //mx_printstr("\033[1S");
    // fprintf(stdout, "%d;%d", start_x, start_y);
    //         fflush(stdout);

    // fprintf(stdout, "%d", y);
    //  fflush(stdout);
//  fprintf(stdout, "\033[%d;%dH", start_x, start_y);
//  fflush(stdout);
int len_line = 5;

    // fprintf(stdout, "\033[%d;%dH", 100, 100);
    // fflush(stdout);

    while (1) {
 

        read (0, &ch, 1);
               mx_get_twidth(&col, &lin);
           //int len_str = 0;
    if (lin != start_x)
        len_str = (((lin+1) - start_x) * col ) - 5;
    else 
        len_str =  col - 5;

            if (n <= len_str) {
            mx_printstr("\033[1K");
            

          
             fprintf(stdout, "\033[%d;%dH", start_x, start_y);
            fflush(stdout);
            mx_printstr("u$h> ");
            //}
            //scanf("\033[%d;%dH", &start_x, &start_y);
            
            //mx_printstr("u$h> ");
            //mx_printstr("\033[1M");
            //mx_printstr("u$h> ");
    


   
        if (ch == 127) {
            back_to_str(&mystr, &n, &len_line);

        }
        else if (ch == '\n') {
            mx_printstr(mystr);
            write(1, "\n", 1);
            if (strcmp("exit", mystr) == 0)
                exit(0);
            break;
        }
        else {
            add_to_str(&mystr, ch, &n, &len_line);
            
        }
 
         if (n-1 == len_str)
                len_line = col;
        //  else {
  
            mx_printstr(mystr);
            }
            else {
                if (len_line == col) {
           
                    fprintf(stdout, "\033[%d;%dH", start_x, 0);
                    fflush(stdout);
                    mx_printstr("\033[0J");
                    mx_printstr("\033[1S");
                    start_x--;
                    fprintf(stdout, "\033[%d;%dH", start_x, 0);
                    fflush(stdout);
                    mx_printstr("u$h> ");
                    len_line = 0;
                    if (ch == 127) 
                        back_to_str(&mystr, &n, &len_line);

                    else if (ch == '\n') {
                        mx_printstr(mystr);
                        write(1, "\n", 1);
                        if (strcmp("exit", mystr) == 0)
                            exit(0);
                        break;
                    }
                    else {
                        add_to_str(&mystr, ch, &n, &len_line);
                        
                    }
                    mx_printstr(mystr);
        
                }
                    
                else {
                             mx_printstr("\033[1K");
            

          
             fprintf(stdout, "\033[%d;%dH", start_x, start_y);
            fflush(stdout);
            mx_printstr("u$h> ");
            //}
            //scanf("\033[%d;%dH", &start_x, &start_y);
            
            //mx_printstr("u$h> ");
            //mx_printstr("\033[1M");
            //mx_printstr("u$h> ");
    


   
        if (ch == 127) {
            back_to_str(&mystr, &n, &len_line);

        }
        else if (ch == '\n') {
            mx_printstr(mystr);
            write(1, "\n", 1);
            if (strcmp("exit", mystr) == 0)
                exit(0);
            break;
        }
        else {
            add_to_str(&mystr, ch, &n, &len_line);
            
        }
  
            mx_printstr(mystr);
                }
    
            }

        // }
    //         mx_printstr("\033[6n");
    //         scanf("\033[%d;%dR", &x, &y);
    //      fprintf(stdout, "x = %d, y = %d, line = %d, col = %d", x, y, lin, col );
    //   fflush(stdout);
      
    }

//     tcsetattr (0, TCSAFLUSH, &savetty);
     return mystr;
}


void lsh_loop(void) {
    char *line;
    int status = 2;
    t_tree **work = NULL;
    t_tree *p = NULL;

    while (1) {
        mx_printstr("u$h> ");
        line = mx_read_line();
        work = mx_works_queue(line);
        for (int i = 0; work[i]; i++) {
            p = work[i];
            for (; (*p).right_child; p = (*p).right_child);
            if ((*p).parent) {
                p = (*p).parent;
                status = mx_redirection((*(*p).right_child).command);
                // printf("\n\nSTATUS = %d\n\n\n", status);
                // if (status == 2)
                    // status = mx_ush_execute((*(*p).right_child).command);
                for (; p != NULL; p = (*p).parent) {
                    if ((*p).operant[1] == '|') {
                        if (status == 1) {
                            status = mx_redirection((*(*p).left_child).command);
                            // printf("\n\nSTATUS = %d\n\n\n", status);
                            // if (status == 2)
                                // status = mx_ush_execute((*(*p).left_child).command);
                        }
                    }
                    else if ((*p).operant[1] == '&') {
                        if (status == 0) {
                            status = mx_redirection((*(*p).left_child).command);
                            // printf("\n\nSTATUS = %d\n\n\n", status);
                            // if (status == 2)
                                // status = mx_ush_execute((*(*p).left_child).command);
                        }
                    }
                }
            }
            else
            {
                status = mx_redirection((*p).command);
                // printf("\n\nSTATUS = %d\n\n\n", status);
                // if (status == 2)
                    // status = mx_ush_execute((*p).command);
            }
        }
        free(line);
    }
}
void hdl(int sig)
{
    sig = sig +1 - 1;
    // printf("%d - pid\n", getpid());
    //printf("\n");
}

int main() {
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



    lsh_loop();
    // lsh_loop();
    // mx_ush_pipe_execute(); 
    
}


