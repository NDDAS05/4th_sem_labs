#include "stack_mod.h"
#include <climits>
#include <cstdlib>
#include <iostream>

int main() {
  stackLib::stk mystack;
  mystack.stack_arr = nullptr;
  int choice, value, size, limit;

  std::cout << "Q2 Part 1. Demonstration" << std::endl;

  while (true) {
    if (mystack.stack_arr == nullptr) {
      std::cout << "Enter 1 to create a stack. 0 to exit.\n" << std::endl;
      std::cout << "Enter option: " << std::endl;
      std::cin >> choice;
      while (choice != 0 && choice != 1) {
        std::cout << "Enter valid choice.\n";
        std::cout << "Enter 1 to create a stack. 0 to exit.\n" << std::endl;
        std::cout << "Enter option: " << std::endl;
      }

      if (choice == 0)
        std::exit(1);
      std::cout << "Enter size (-1 to set to deafult):";
      std::cin >> size;
      if (size == -1 || size == 0) {
        stackLib::initialize(mystack);
        std::cout << "Initialized with default size." << std::endl;
      } 
      else {
        std::cout << "Enter maximum capacity (-1 to set to default): ";
        std::cin >> limit;
        if (limit == 0 || limit == -1) {
          std::cout << "Initialized with default capacity." << std::endl;
          stackLib::initialize(mystack, size);
        }
        else stackLib::initialize(mystack, size, limit);
      }

      while (true) {
        std::cout << "Choose option: " << std::endl;
        std::cout << "\t1. Push Element" << std::endl;
        std::cout << "\t2. Push multiple elements" << std::endl;
        std::cout << "\t3. Pop element" << std::endl;
        std::cout << "\t4. Print stack" << std::endl;
        std::cout << "\t5. Print current size" << std::endl;
        std::cout << "\t6. Print maximum capacity" << std::endl;
        std::cout << "\t7. Clear and exit" << std::endl;
        std::cout << "\nEnter choice: ";
        std::cin >> choice;
        if (choice == 7) {
          stackLib::release(mystack);
          break;
        }

        switch (choice) {
        case 1:
          std::cout << "Enter element to push: ";
          std::cin >> value;
          if (stackLib::push(mystack, value))
            std::cout << value << " pushed." << std::endl;
          else
            std::cout << "Error occured." << std::endl;
          break;
        case 2: {
          std::cout << "Enter number of elements to push: \n";
          std::cin >> value;
          std::cout << "Enter values.\n";
          int *arr = new int[value];
          for (int i = 0; i < value; i++) {
            std::cin >> arr[i];
          }
          if (stackLib::push(mystack, arr, value))
            std::cout << "Array pushed.\n";
          else
            std::cout << "Could not push all data. Last element pushed: "
                      << mystack.stack_arr[mystack.top] << std::endl;
          delete[] arr;
          break;
        }
        case 3:
          value = stackLib::pop(mystack);
          if (value != INT_MIN)
            std::cout << "Popped with value: " << value << std::endl;
          break;
        case 4:
          stackLib::display(mystack);
          break;
        case 5:
          std::cout << mystack.top + 1 << std::endl;
          break;
        case 6:
          std::cout << mystack.MaxLimit << std::endl;
          break;
        default:
          std::cout << "Enter valid choice." << std::endl;
        }
      }
    }
  }
}