#ifndef STACK_MOD_H
#define STACK_MOD_H

#include <iostream>

namespace stackLib {

typedef struct growing_stack {
  int *stack_arr;
  int top;
  int capacity;
  int MaxLimit;
} stk;

inline bool isempty(const stk &s) { return s.top == -1; }

inline int currentSize(const stk &s) { return s.top + 1; }

inline int maxSize(const stk &s) { return s.MaxLimit; }

void initialize(stk &s, const int &initialSize = 10, const int &MaxLimit = 100);
void release(stk &s);
int inflate(stk &s);
int push(stk &s, const int &elem);
int push(stk &s, int *const arr, const int &count);
int pop(stk &s);
void display(const stk &s);

} // namespace stackLib

#endif // !STACK_MOD_H
