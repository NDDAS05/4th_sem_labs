#include "stack_mod.h"
#include <climits>

namespace stackLib {

    stk::stk()
    {
        stack_arr = nullptr;
        top = -1;
        capacity = 0;
        MaxLimit = 0;
    }

    stk::stk(const stk &other)
    {
        capacity = other.capacity;
        MaxLimit = other.MaxLimit;
        top = other.top;

        if (capacity > 0)
        {
            stack_arr = new int[capacity];

            for (int i = 0; i <= top; i++)
                stack_arr[i] = other.stack_arr[i];
        }
        else
            stack_arr = nullptr;
    }

    stk& stk::operator=(const stk &other)
    {
        if (this == &other)
            return *this;

        delete[] stack_arr;

        capacity = other.capacity;
        MaxLimit = other.MaxLimit;
        top = other.top;

        if (capacity > 0)
        {
            stack_arr = new int[capacity];

            for (int i = 0; i <= top; i++)
                stack_arr[i] = other.stack_arr[i];
        }
        else
            stack_arr = nullptr;

        return *this;
    }

    stk::~stk()
    {
        delete[] stack_arr;
    }

    void stk::initialize(int initialSize, int MaxLimit)
    {
        delete[] stack_arr;

        this->capacity = initialSize;
        this->MaxLimit = MaxLimit;
        this->top = -1;

        stack_arr = new int[capacity];
    }

    bool stk::isEmpty() const
    {
        return top == -1;
    }

    int stk::currentSize() const
    {
        return top + 1;
    }

    int stk::getMaxSize() const
    {
        return MaxLimit;
    }

    int stk::inflate()
    {
        if (capacity >= MaxLimit)
            return 0;

        int newCap = capacity * 2;

        if (newCap > MaxLimit)
            newCap = MaxLimit;

        int *newArr = new int[newCap];

        for (int i = 0; i <= top; i++)
            newArr[i] = stack_arr[i];

        delete[] stack_arr;

        stack_arr = newArr;
        capacity = newCap;

        return 1;
    }

    int stk::push(int elem)
    {
        if(stack_arr == nullptr) 
            return 0;

        if (top == capacity - 1) {

            if (!inflate()) {
                std::cout << "Stack overlowed.\n";
                return 0;
            }
        }

        stack_arr[++top] = elem;

        return 1;
    }

    int stk::push(int *arr, int count)
    {
        for (int i = 0; i < count; i++)
            if (!push(arr[i]))
                return 0;

        return 1;
    }

    int stk::pop()
    {
        if (isEmpty()) {
            std::cout << "Stack underflowed.\n";
            return INT_MIN;
        }

        return stack_arr[top--];
    }

    void stk::display() const
    {
        if (stack_arr == nullptr)
        {
            std::cout << "Stack not initialized.\n";
            return;
        }
        std::cout << "[ ";

        for (int i = 0; i <= top; i++)
            std::cout << stack_arr[i] << " ";

        std::cout << "]\n";
    }

}
