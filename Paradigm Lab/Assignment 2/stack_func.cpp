#include "stack_mod.h"
#include <climits>
#include <iostream>

namespace stackLib {

void initialize(stk &s, const int &initialSize,
                const int &MaxLimit) { // Initialized in stack_mod.h file
  s.MaxLimit = MaxLimit;
  s.capacity = initialSize;
  s.top = -1;
  s.stack_arr = new int[s.capacity];
}

void release(stk &s) {
  if (s.stack_arr != nullptr) {
    delete[] s.stack_arr;
    s.stack_arr = nullptr;
  }
  s.top = -1;
}

int inflate(stk &s) {
  if (s.capacity >= s.MaxLimit)
    return 0;

  int newCap = s.capacity * 2;
  if (newCap > s.MaxLimit)
    newCap = s.MaxLimit;

  std::cout << "[Inflating stack]" << std::endl;

  int *newArr = new int[newCap];

  for (int i = 0; i <= s.top; i++)
    newArr[i] = s.stack_arr[i];

  delete[] s.stack_arr;

  s.stack_arr = newArr;
  s.capacity = newCap;

  return 1;
}

int push(stk &s, const int &elem) {
  if (s.top == s.capacity - 1)
    if (!inflate(s)) {
      std::cout << "Stack Overflow. Can not inflate any more." << std::endl;
      return 0;
    }

  s.stack_arr[++s.top] = elem;
  return 1;
}

int push(stk &s, int *const arr, const int &count) {
  for (int i = 0; i < count; i++) {
    if (!push(s, arr[i])) {
      return 0;
    }
  }
  return 1;
}

int pop(stk &s) {
  if (isempty(s)) {
    std::cout << "Stack underflow." << std::endl;
    return INT_MIN;
  }

  int result = s.stack_arr[s.top];
  s.top--;
  return result;
}

void display(const stk &s) {
  std::cout << "[ ";
  for (int i = 0; i <= s.top; i++) {
    std::cout << s.stack_arr[i] << " ";
  }
  std::cout << "]\n";
}
}
