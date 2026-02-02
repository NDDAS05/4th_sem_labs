#ifndef STRING_MOD_H
#define STRING_MOD_H

#include <cctype>
#include <cstring>

namespace string_mod
{
    int string_comp(char* s1, char* s2);
    bool if_palindrome(char *s, int start, int end);
    void replace(char* str, char ch1, char ch2);
    char min_char(char* str, int size);
}

#endif
