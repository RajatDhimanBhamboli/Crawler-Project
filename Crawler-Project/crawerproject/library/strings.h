#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <cstdlib>

int stringlength(const char* str);
bool my_strcmp(const char* a, const char* b);
char* my_strcat(char* dest, const char* src);
char* my_strcpy(char* dest, const char* src);
char* my_strchr(const char* s, int c);
char* my_strstr(const char* haystack, const char* needle);
char* my_strcasestr(const char* haystack, const char* needle);
char* lowercase(const char* haystack);
char* normalize_whitespace(const char* str);
void reverse_inplace(char* s);
int is_palindrome(const char* s);
int count_words(const char* s);
char* placeholder(char* templates, const char* data[], int size);

#endif