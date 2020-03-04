 #include "header.h"

 void mx_byte_check_add(unsigned char *ch, int *delte_len, int *delta_byte,
                       int start) {
    if (ch[start] >> 7 == 0)
        *delta_byte = 1;
    if (ch[start] >> 5 == 6 && ch[start + 1] >> 6 == 2 )
        *delta_byte = 2;
    if (ch[start] >> 4 == 14 && ch[start + 1] >> 6 == 2
        && ch[start + 2] >> 6 == 2 )
        *delta_byte = 3;
    if (ch[start] >> 3 == 30 && ch[start + 1] >> 6 == 2 
        && ch[start + 2] >> 6 == 2 && ch[start + 3] >> 6 == 2) {
        *delta_byte = 4;
        *delte_len = 2;
    }
}

void mx_byte_check_back(unsigned char *str, int *len, int *minus, int n) {
    if ( str[n-2] >> 7 == 0)
        *minus = 1;
    if (str[n-3] >> 5 == 6 && str[n-2] >> 6 == 2 )
        *minus = 2;
    if (str[n-4] >> 4 == 14 && str[n-3] >> 6 == 2 && str[n-2] >> 6 == 2 )
        *minus = 3;
    if (str[n-5] >> 3 == 30 && str[n-4] >> 6 == 2 && str[n-3] >> 6 == 2
        && str[n-2] >> 6 == 2) {
        *minus = 4;
        *len = 2;
    }
}

