#include "array_mod.h"
#include <iostream>

namespace array_mod
{
    int* init(int size)
    {
        return new int[size];
    }

    int* free_arr(int* arr)
    {
        delete[] arr;
        return nullptr;
    }

    int max_num(int *arr, int size)
    {
        if(size == 1) return arr[0];
        int m = max_num(arr, size-1);
        return (arr[size-1] > m) ? arr[size-1] : m;
    }

    bool lin_search(int* arr, int size, int elem)
    {
        if(size == 0) return false;
        if(arr[size-1] == elem) return true;
        return lin_search(arr, size-1, elem);
    }

    void print_reverse(int* arr, int size)
    {
        if(size == 0) return;
        std::cout << arr[size-1] << " ";
        print_reverse(arr, size-1);
    }

    int sumArr(int* arr, int size, int index)
    {
        if(index == size-1) return arr[index];
        return arr[index] + sumArr(arr, size, index+1);
    }
}
