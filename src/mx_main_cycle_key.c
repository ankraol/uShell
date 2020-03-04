 #include "header.h"

// void add_to_str(unsigned char **str, t_len_name **le) {
//     int plus = 0;
//     int len = 1;
//     int buf_plus = 0;
//     unsigned char *buf_str = NULL;

//     mx_byte_check_add((*le)->ch, &len, &plus, 0);
//     if ((*le)->ch[0] >> 7 == 0 && (*le)->ch[1] >> 7 == 0 && (*le)->ch[2] >> 7 == 0 && (*le)->ch[3] >> 7 == 0 && (*le)->ch[1] != 0 && (*le)->ch[2] != 0 && (*le)->ch[3] != 0) {
//         plus = 4;
//         len = 4;
// }

//     if ((*le)->n_cursor_b == (*le)->n_bute) {
//         (*le)->n_bute = (*le)->n_bute + plus;
//         (*le)->n_cursor_b = (*le)->n_cursor_b + plus;
//         (*le)->n_len = (*le)->n_len + len;
//         (*le)->n_cursor = (*le)->n_cursor + len;
//         (*str) = (unsigned char *)realloc(*str, (*le)->n_bute);
//         (*str)[((*le)->n_bute)-1] = '\0';
//         buf_plus = plus;
//         for (int i = 0; i < plus; i++) {
//             (*str)[((*le)->n_bute)-1-buf_plus] = (*le)->ch[i];
//             buf_plus--;
//         }
//     }
//     else {
//         buf_str = (unsigned char *)malloc(sizeof(char) * (((*le)->n_bute) + plus));
//         for (int i = 0; i < (*le)->n_cursor_b - 1; i++)
//             buf_str[i] = (*str)[i];
//         for (int i = 0; i < plus; i++)
//             buf_str[(*le)->n_cursor_b + i - 1] = (*le)->ch[i];
//         for (int i = (*le)->n_cursor_b + plus - 1; i <= (*le)->n_bute; i++)
//             buf_str[i] = (*str)[i - plus];
//         free(*str);
//         *str = buf_str;
//         (*le)->n_bute = (*le)->n_bute + plus;
//         (*le)->n_cursor_b = (*le)->n_cursor_b + plus;
//         (*le)->n_cursor = (*le)->n_cursor + len;
//         (*le)->n_len = (*le)->n_len + len;
//     }

// }

void back_to_str(unsigned char **str,  t_len_name **le) {
    int minus = 0;
    int len = 1;
    unsigned char *buf_str = NULL;
    int q = 0;

    mx_byte_check_back(*str, &len, &minus, (*le)->n_bute);
    if ((*le)->n_cursor_b == (*le)->n_bute) {
        if ((*le)->n_bute > 1) {
            for (int i = 0; i < minus; i++) {
            (*str)[(*le)->n_bute- 2 - i] = '\0';
        }
        (*le)->n_bute = (*le)->n_bute - minus;
        (*str) = (unsigned char *)realloc(*str, (*le)->n_bute);
        (*le)->n_len = (*le)->n_len - len;
        (*le)->n_cursor = (*le)->n_cursor - len;
        (*le)->n_cursor_b = (*le)->n_cursor_b - minus;
        }
    }
    else {
        if ((*le)->n_cursor_b > 1) {
            buf_str = (unsigned char *)malloc(sizeof(char) * ((*le)->n_bute  - minus));
            for (int i = 0; i < (*le)->n_cursor_b - minus - 1; i++)
                buf_str[i] = (*str)[i];
            q = (*le)->n_cursor_b - minus - 1;
            for (int i = (*le)->n_cursor_b - 1; i < (*le)->n_bute; i++) {
                buf_str[q] = (*str)[i];
                q++;
            }
            free(*str);
            *str = buf_str;
            (*le)->n_len = (*le)->n_len - len;
            (*le)->n_cursor = (*le)->n_cursor - len;
            (*le)->n_cursor_b = (*le)->n_cursor_b - minus;
            (*le)->n_bute = (*le)->n_bute - minus;
        }
        
    }
}

static void push_and_free(t_history_name **history, unsigned char **mystr, 
                    t_len_name *len, char *buf_first) {
    if ((*mystr)[0] != 0)
        mx_push_back_history(history, *mystr, len);
    if (len->first_line != true)
        free(buf_first);
}

static void read_and_width(t_len_name *len) {
    read (0, len->ch, 4);
    mx_get_width(&(len->col));
}

static bool check_for_byte(t_len_name *len) {
    if (len->ch[0] == 127 && len->ch[1] == 0 && len->ch[2] == 0 
        && len->ch[3] == 0) {
            return true;
        }
    return false;
}



void mx_main_cycle_key(t_history_name **history, unsigned char **mystr, 
                       t_len_name *len, char *buf_first) {
    t_history_name *his = *history;

    while (1) {
        read_and_width(len);
        if (len->ch[0] != 27 && len->ch[0] != 9 ) {
            mx_one_cycle(mystr, len, len->buf);
            if (check_for_byte(len) == true)
                back_to_str(mystr, &len);
            else if (len->ch[0] == '\n' || len->ch[0] == '\0') {
                mx_two_cycle(history, mystr, len, buf_first);
                break;
            }
            else if (len->ch[0] != 27) 
                mx_add_to_str(mystr, &len);
            mx_three_cycle(mystr, len);
        }
        mx_four_cycle(mystr, len, &buf_first, &his);
    }
    push_and_free(history, mystr, len, buf_first);
}
