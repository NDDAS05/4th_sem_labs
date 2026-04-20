#ifndef ARRAY_MOD_H
#define ARRAY_MOD_H

namespace array_mod
{
    int* init(int size);
    int* free_arr(int* arr);
    int max_num(int *arr, int size);
    bool lin_search(int* arr, int size, int elem);
    void print_reverse(int* arr, int size);
    int sumArr(int* arr, int size, int index);
}

#endif
