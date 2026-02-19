#include "stack_mod.h"
#include <iostream>
#include <climits>

using namespace stackLib;

int main()
{
    stk stack1, stack2;
    stk* current = nullptr;

    int mainChoice, choice, value, size, limit;

    while(true)
    {
        std::cout<<"\nSelect action:\n";
        std::cout<<"1. Use stack 1\n";
        std::cout<<"2. Use stack 2\n";
        std::cout<<"3. Display both stacks\n";
        std::cout<<"0. Exit\n";
        std::cout<<"Choice: ";
        std::cin>>mainChoice;

        if(mainChoice == 0)
            break;

        if(mainChoice == 3)
        {
            std::cout<<"\nStack 1: ";
            stack1.display();

            std::cout<<"Stack 2: ";
            stack2.display();

            continue;
        }

        if(mainChoice == 1)
            current = &stack1;
        else if(mainChoice == 2)
            current = &stack2;
        else
            continue;


        while(true)
        {
            std::cout<<"\nChoose an option:\n";
            std::cout<<"1. Initialize\n";
            std::cout<<"2. Push\n";
            std::cout<<"3. Pop\n";
            std::cout<<"4. Display\n";
            std::cout<<"5. Size\n";
            std::cout<<"6. Max Size\n";
            std::cout<<"7. Back\n";
            std::cout<<"Choice: ";
            std::cin>>choice;

            if(choice == 7)
                break;

            switch(choice)
            {
                case 1:
                    std::cout<<"Enter size and max limit: ";
                    std::cin>>size>>limit;
                    current->initialize(size,limit);
                    break;

                case 2:
                    std::cout<<"Enter value: ";
                    std::cin>>value;
                    current->push(value);
                    break;

                case 3:
                    value=current->pop();
                    if(value!=INT_MIN)
                        std::cout<<"Popped "<<value<<std::endl;
                    break;

                case 4:
                    current->display();
                    break;

                case 5:
                    std::cout<<"Size: "<<current->currentSize()<<std::endl;
                    break;

                case 6:
                    std::cout<<"Max Size: "<<current->getMaxSize()<<std::endl;
                    break;
            }
        }
    }
}
