#ifndef _LIBMIX_H_
#define _LIBMIX_H_

#include <stdlib.h>
#include <unistd.h>
#include <wchar.h>
#include <fcntl.h>
#include <stdbool.h>

int mx_count_words(const char *str, char c);
char *mx_strnew(const int size);
char **mx_strsplit(const char *s, char c);
int mx_strlen(const char *s);
void mx_del_strarr(char ***arr);
char *mx_strjoin( char *s1,  char *s2);
char *mx_strcat(char *restrict s1, const char *restrict s2);
void mx_strdel(char **str);
char *mx_itoa(int number);
char *mx_file_to_str(const char *file);
void mx_printstr(const char *s);
int mx_strcmp(const char *s1, unsigned const char *s2);
void mx_printchar(char c);
char *mx_strcpy(char *dst, const char *src);
char *mx_strdup(const char *s1);
int mx_strncmp(const char *s1, const char *s2, int n);
char *mx_strstr(const char *haystack, const char *needle);
bool mx_isdigit(int c);

#endif
