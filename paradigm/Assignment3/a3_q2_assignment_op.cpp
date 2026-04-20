#include "stack_mod.h"
#include <iostream>

using namespace stackLib;

int main()
{
    stk stack1, stack2;

    int choice, value, size, limit;

    while(true)
    {
        std::cout<<"\n1. Initialize Stack1\n";
        std::cout<<"2. Initialize Stack2\n";
        std::cout<<"3. Push Stack1\n";
        std::cout<<"4. Push Stack2\n";
        std::cout<<"5. Display both\n";
        std::cout<<"6. Assign Stack2 = Stack1\n";
        std::cout<<"0. Exit\n";
        std::cout<<"Choice: ";

        std::cin>>choice;

        if(choice==0)
            break;

        switch(choice)
        {
            case 1:
                std::cout<<"Enter size and limit: ";
                std::cin>>size>>limit;
                stack1.initialize(size,limit);
                break;

            case 2:
                std::cout<<"Enter size and limit: ";
                std::cin>>size>>limit;
                stack2.initialize(size,limit);
                break;

            case 3:
                std::cin>>value;
                stack1.push(value);
                break;

            case 4:
                std::cin>>value;
                stack2.push(value);
                break;

            case 5:
                std::cout<<"Stack1: ";
                stack1.display();

                std::cout<<"Stack2: ";
                stack2.display();
                break;

            case 6:
                stack2 = stack1;
                std::cout<<"Assignment complete.\n";
                break;
        }
    }
}
