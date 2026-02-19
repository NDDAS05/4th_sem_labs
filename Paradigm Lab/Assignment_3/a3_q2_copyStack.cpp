#include "stack_mod.h"
#include <iostream>

using namespace stackLib;

int main()
{
    stk original;
    stk copy;

    int choice, value, size, limit;
    bool copied=false;

    while(true)
    {
        std::cout<<"\n1. Initialize Original\n";
        std::cout<<"2. Push into Original\n";
        std::cout<<"3. Create Copy (Copy Constructor)\n";
        std::cout<<"4. Display Original\n";
        std::cout<<"5. Display Copy\n";
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
                original.initialize(size,limit);
                break;

            case 2:
                std::cout<<"Enter value: ";
                std::cin>>value;
                original.push(value);
                break;

            case 3:
                copy = stk(original); 
                copied=true;
                std::cout<<"Copy created.\n";
                break;

            case 4:
                std::cout<<"Original: ";
                original.display();
                break;

            case 5:
                if(copied)
                {
                    std::cout<<"Copy: ";
                    copy.display();
                }
                else
                    std::cout<<"Copy not created yet.\n";
                break;
        }
    }
}
