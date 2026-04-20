#include "stack_mod.h"
#include <iostream>

using namespace stackLib;

int main() {
  stk original;
  stk copy;

  int choice, value, size, limit;
  bool copied = false;
  bool originalInit = false;

  while (true) {
    std::cout << "\n";

    if (!originalInit) {
      std::cout << "1. Initialize Original\n";
    } else {
      std::cout << "2. Push into Original\n";
      std::cout << "3. Create Copy (Copy Constructor)\n";
      std::cout << "4. Display Original\n";
    }

    if (copied) {
      std::cout << "5. Display Copy\n";
    }

    std::cout << "0. Exit\n";
    std::cout << "Choice: ";

    std::cin >> choice;

    if (choice == 0)
      break;

    if (!originalInit && choice != 1) {
      std::cout << "Error: Initialize the original stack first.\n";
      continue;
    }

    if (!copied && choice == 5) {
      std::cout << "Error: Copy not created.\n";
      continue;
    }

    switch (choice) {
    case 1:
      if (!originalInit) {
        std::cout << "Enter size and limit: ";
        std::cin >> size >> limit;
        original.initialize(size, limit);
        originalInit = true;
      } else {
        std::cout << "Invalid choice. Stack is already initialized.\n";
      }
      break;

    case 2:
      std::cout << "Enter value: ";
      std::cin >> value;
      if (original.push(value) == 0) {
        std::cout << "Push Failed.\n";
      }
      break;

    case 3:
      copy = stk(original);
      copied = true;
      std::cout << "Copy created.\n";
      break;

    case 4:
      std::cout << "Original: ";
      original.display();
      break;

    case 5:
      std::cout << "Copy: ";
      copy.display();
      break;

    default:
      std::cout << "Invalid choice.\n";
      break;
    }
  }

  return 0;
}
