#include "stack_mod.h"
#include <climits>
#include <cstdlib>
#include <iostream>


int main() {

  stackLib::stk stack1;
  stackLib::stk stack2;

  stack1.stack_arr = nullptr;
  stack2.stack_arr = nullptr;

  int mainChoice, subChoice, value, size, limit;
  

  stackLib::stk *currentStackPtr = nullptr; //To point to a stack

  std::cout << "Q2 Part 2. Simultaneous Existance of more than 1 stack" << std::endl;

  while (true) {

    std::cout << "Choose an option:" << std::endl;
    std::cout << "\t1. Operate on Stack 1" << std::endl;
    std::cout << "\t2. Operate on Stack 2" << std::endl;
    std::cout << "\t3. View Status of both Stacks" << std::endl;
    std::cout << "\t0. Exit Program" << std::endl;
    std::cout << "Enter choice: ";
    std::cin >> mainChoice;

    if (mainChoice == 0) {
      stackLib::release(stack1);
      stackLib::release(stack2);
      std::exit(0);
    } 
    else if (mainChoice == 3) {

      std::cout << "Stack 1: ";
      if(stack1.stack_arr == nullptr) {
          std::cout << "Empty" << std::endl;
      } else {
          stackLib::display(stack1);
          std::cout << "Size: (" << stackLib::currentSize(stack1) 
                    << "/" << stack1.MaxLimit << ")" << std::endl;
      }

      std::cout << "Stack 2: ";
      if(stack2.stack_arr == nullptr) {
          std::cout << "Empty" << std::endl;
      } else {
          stackLib::display(stack2);
          std::cout << "Size: (" << stackLib::currentSize(stack2) 
                    << "/" << stack2.MaxLimit << ")" << std::endl;
      }
      continue;
    }
    else if (mainChoice == 1) {
        currentStackPtr = &stack1;
    } 
    else if (mainChoice == 2) {
        currentStackPtr = &stack2;
    } 
    else {
        std::cout << "Invalid choice." << std::endl;
        continue;
    }

    stackLib::stk &currentStack = *currentStackPtr; // currentStack references the stack currently being operted
    bool mainMenu = false; // To return to menu or switch stack

    if (currentStack.stack_arr == nullptr) {
      std::cout << "Stack " << mainChoice << " is not initialized." << std::endl;
      std::cout << "1. Initialize" << std::endl;
      std::cout << "0. Back to menu" << std::endl;
      std::cout << "Choice: ";
      std::cin >> subChoice;
      
      if (subChoice == 0) continue;

      std::cout << "Enter size (-1 for default): ";
      std::cin >> size;
      if (size == -1 || size == 0) {
        stackLib::initialize(currentStack);
        std::cout << "Initialized with default values." << std::endl;
      } else {
        std::cout << "Enter max capacity (-1 for default): ";
        std::cin >> limit;
        if (limit == 0 || limit == -1) 
          stackLib::initialize(currentStack, size);
        else 
          stackLib::initialize(currentStack, size, limit);
      }
    }

    while (!mainMenu) {
        std::cout << "Stack " << mainChoice << std::endl;
        std::cout << "1. Push Element" << std::endl;
        std::cout << "2. Push Array" << std::endl;
        std::cout << "3. Pop Element" << std::endl;
        std::cout << "4. Print Stack" << std::endl;
        std::cout << "5. Check Status (Size/Limit)" << std::endl;
        std::cout << "6. Clear" << std::endl;
        std::cout << "9. Switch Stack" << std::endl;
        std::cout << "Enter choice: ";
        std::cin >> subChoice;

        switch (subChoice) {
            case 1:
                std::cout << "Enter value to push: ";
                std::cin >> value;
                if(stackLib::push(currentStack, value))
                    std::cout << "Pushed." << std::endl;
                else 
                    std::cout << "Could not push element." << std::endl;
                break;
            case 2: {
                std::cout << "Enter number of values to push: ";
                std::cin >> value;
                int *arr = new int[value];
                std::cout << "Enter values: ";
                for(int i=0; i<value; i++) std::cin >> arr[i];
                stackLib::push(currentStack, arr, value);
                delete[] arr;
                break;
            }
            case 3:
                value = stackLib::pop(currentStack);
                if(value != INT_MIN)
                    std::cout << "Popped value: " << value << std::endl;
                break;
            case 4:
                std::cout << "Stack " << mainChoice << ": ";
                stackLib::display(currentStack);
                break;
            case 5:
                std::cout << "Size: " << stackLib::currentSize(currentStack) <<std::endl;
                std::cout<< "Max: " << currentStack.MaxLimit << std::endl;
                break;
            case 6:
                stackLib::release(currentStack);
                std::cout << "Stack released." << std::endl;
                mainMenu = true;
                break;
            case 9:
                mainMenu = true;
                break;
            default:
                std::cout << "Invalid choice." << std::endl;
        }
    }
  }
}