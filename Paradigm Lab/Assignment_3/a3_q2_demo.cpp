#include "stack_mod.h"
#include <iostream>
#include <climits>

using namespace stackLib;

int main()
{
    stk stack;
    int choice, value, size, limit;

    while(true)
    {
        std::cout<<"\n1. Initialize stack\n2. Push\n3. Pop\n4. Display\n5. Show size\n6. Show max-size\n0. Exit\n";
        std::cin>>choice;

        switch(choice)
        {

        case 1:
            std::cout<<"Enter size and max limit: ";
            std::cin>>size>>limit;
            stack.initialize(size,limit);
            break;

        case 2:
            std::cin>>value;
            stack.push(value);
            break;

        case 3:
            value=stack.pop();
            if(value!=INT_MIN)
                std::cout<<"Popped: "<<value<<std::endl;
            break;

        case 4:
            stack.display();
            break;

        case 5:
            std::cout<<"Size: "<<stack.currentSize()<<std::endl;
            break;

        case 6:
            std::cout<<"Max: "<<stack.getMaxSize()<<std::endl;
            break;

        case 0:
            return 0;
        }
    }
}
