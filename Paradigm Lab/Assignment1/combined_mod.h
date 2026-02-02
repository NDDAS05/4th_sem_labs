#ifndef COMBINED_H
#define COMBINED_H

#include <cctype>
#include <cstring>

namespace combined_mod
{
    int string_comp(char* s1, char* s2);

    int* init(int size);
    int* free_arr(int* arr);
    int max_num(int *arr, int size);

    bool lin_search(int* arr, int size, int elem);
    void print_reverse(int* arr, int size);

    bool if_palindrome(char *s, int start, int end);
    void replace(char* str, char ch1, char ch2);

    int sumArr(int* arr, int size, int index);
    char min_char(char* str, int size);
}

#endif
