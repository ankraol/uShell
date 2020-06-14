 #include "header.h"

static void first(t_len_name **le, unsigned char **str, int plus, int len) {
    (*le)->n_bute = (*le)->n_bute + plus;
    (*le)->n_cursor_b = (*le)->n_cursor_b + plus;
    (*le)->n_len = (*le)->n_len + len;
    (*le)->n_cursor = (*le)->n_cursor + len;
    (*str) = (unsigned char *)realloc(*str, (*le)->n_bute);
    (*str)[((*le)->n_bute)-1] = '\0';
}

static void second(t_len_name **le, unsigned char **buf_str,
                   unsigned char **str, int plus) {
    *buf_str =
            (unsigned char *)malloc(sizeof(char) * (((*le)->n_bute) + plus));
    for (int i = 0; i < (*le)->n_cursor_b - 1; i++)
        (*buf_str)[i] = (*str)[i];
    for (int i = 0; i < plus; i++)
        (*buf_str)[(*le)->n_cursor_b + i - 1] = (*le)->ch[i];
    for (int i = (*le)->n_cursor_b + plus - 1; i <= (*le)->n_bute; i++)
        (*buf_str)[i] = (*str)[i - plus];
    free(*str);
    *str = *buf_str;
}

static void third(t_len_name **le, int plus, int len) {
    (*le)->n_bute = (*le)->n_bute + plus;
    (*le)->n_cursor_b = (*le)->n_cursor_b + plus;
    (*le)->n_cursor = (*le)->n_cursor + len;
    (*le)->n_len = (*le)->n_len + len;
}

static void forth(t_len_name **le, int *plus, int *len) {
    if ((*le)->ch[0] >> 7 == 0 && (*le)->ch[1] >> 7 == 0
        && (*le)->ch[2] >> 7 == 0 && (*le)->ch[3] >> 7 == 0 
        && (*le)->ch[1] != 0 && (*le)->ch[2] != 0 
        && (*le)->ch[3] != 0 && (*le)->ch[3] != 10) {
        *plus = 4;
        *len = 4;
    }
    else if ((*le)->ch[0] >> 7 == 0 && (*le)->ch[1] >> 7 == 0
            && (*le)->ch[2] >> 7 == 0 && (*le)->ch[0] != 0 && (*le)->ch[1] != 0 
            && (*le)->ch[2] != 0 && (*le)->ch[2] != 10) {
            *plus = 3;
            *len = 3;
    }
    else if ((*le)->ch[0] >> 7 == 0 && (*le)->ch[1] >> 7 == 0
            && (*le)->ch[0] != 0 && (*le)->ch[1] != 0 && (*le)->ch[1] != 10) {
            *plus = 2;
            *len = 2;
    }
}


void mx_add_to_str(unsigned char **str, t_len_name **le) {
    int plus = 0;
    int len = 1;
    int buf_plus = 0;
    unsigned char *buf_str = NULL;

    if ((*le)->ch[0] == 4 && *str[0] != 0)
        return;
    mx_byte_check_add((*le)->ch, &len, &plus, 0);
    forth(le, &plus, &len);
    if ((*le)->n_cursor_b == (*le)->n_bute) {
        first(le, str, plus, len);
        buf_plus = plus;
        for (int i = 0; i < plus; i++) {
            (*str)[((*le)->n_bute)-1-buf_plus] = (*le)->ch[i];
            buf_plus--;
        }
    }
    else {
        second(le, &buf_str, str, plus);
        third(le, plus, len);
    }
}
