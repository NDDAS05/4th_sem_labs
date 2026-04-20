#include "string_mod.h"

namespace string_mod
{
    int string_comp(char* s1, char* s2)
    {
        if(s1[0]=='\0' && s2[0]=='\0') return 0;
        if(s1[0] == s2[0]) return string_comp(s1+1, s2+1);
        if(s1[0] < s2[0]) return 1;
        return -1;
    }

    bool if_palindrome(char *s, int start, int end)
    {
        if(start >= end) return true;
        if(std::tolower(s[start]) != std::tolower(s[end])) return false;
        return if_palindrome(s, start+1, end-1);
    }

    void replace(char* str, char ch1, char ch2)
    {
        if(str[0] == '\0') return;
        if(str[0] == ch1) str[0] = ch2;
        replace(str+1, ch1, ch2);
    }

    char min_char(char* str, int size)
    {
        if(size == 1) return str[0];
        char m = min_char(str+1, size-1);
        return (str[0] < m) ? str[0] : m;
    }
}
