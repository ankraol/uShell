#include "header.h"

static void first(unsigned char **str, t_len_name **le, int minus, int len) {
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

static void second(unsigned char **str,  t_len_name **le, 
                   unsigned char **buf_str, int minus) {
    int q = 0;

    *buf_str = (unsigned char *)malloc(sizeof(char) * ((*le)->n_bute - minus));
    for (int i = 0; i < (*le)->n_cursor_b - minus - 1; i++)
        (*buf_str)[i] = (*str)[i];
    q = (*le)->n_cursor_b - minus - 1;
    for (int i = (*le)->n_cursor_b - 1; i < (*le)->n_bute; i++) {
        (*buf_str)[q] = (*str)[i];
        q++;
    }
    free(*str);
    *str = *buf_str;
}

void mx_back_to_str(unsigned char **str, t_len_name **le) {
    int minus = 0;
    int len = 1;
    unsigned char *buf_str = NULL;

    mx_byte_check_back(*str, &len, &minus, (*le)->n_bute);
    if ((*le)->n_cursor_b == (*le)->n_bute)
        first(str, le, minus, len);
    else {
        if ((*le)->n_cursor_b > 1) {
            second(str, le, &buf_str, minus);
            (*le)->n_len = (*le)->n_len - len;
            (*le)->n_cursor = (*le)->n_cursor - len;
            (*le)->n_cursor_b = (*le)->n_cursor_b - minus;
            (*le)->n_bute = (*le)->n_bute - minus;
        }
    }
}
