#ifndef STACK_MOD_H
#define STACK_MOD_H

#include <iostream>

namespace stackLib {

    class stk {

    private:

        int *stack_arr;
        int top;
        int capacity;
        int MaxLimit;

        int inflate();

    public:

        stk();
        stk(const stk &other);
        stk& operator=(const stk &other);
        ~stk();

        void initialize(int initialSize = 10, int MaxLimit = 100);
        int push(int elem);
        int push(int *arr, int count);
        int pop();
        bool isEmpty() const;
        int currentSize() const;
        int getMaxSize() const;

        void display() const;
    };

}

#endif
