#include "stack_mod.h"
#include<iostream>

int main()
{
    using std::cin;
    using std::cout;
    using std::endl;

    int size, limit, choice, value;

    stackLib::stk stack1;
    stackLib::stk stack2;

    cout<<"Initializing Stack 1\n"<<endl;
    cout<<"Enter initial size (-1 to set to default): ";
    cin>>size;

    if(size <= 0)
        stack1.initialize();
    else
    {
        cout<<"Enter maximum limit (-1 to set to default): ";
        cin>>limit;

        if(limit <= 0)
            stack1.initialize(size);
        else
            stack1.initialize(size, limit);
    }

    cout<<"Initializing Stack 2\n"<<endl;
    cout<<"Enter initial size (-1 to set to default): ";
    cin>>size;

    if(size <= 0)
        stack2.initialize();
    else
    {
        cout<<"Enter maximum limit (-1 to set to default): ";
        cin>>limit;

        if(limit <= 0)
            stack2.initialize(size);
        else
            stack2.initialize(size, limit);
    }

    // Stack 1 input
    cout<<"\n[Stack 1]\n";

    while(true)
    {
        cout<<"\nChoose option:\n";
        cout<<"1 Push\n";
        cout<<"0 Go to stack 2\n";
        cin>>choice;

        if(choice == 1)
        {
            cout<<"Enter value: ";
            cin>>value;

            if(!stack1.push(value))
            {
                cout<<"Stack full.\n";
                break;
            }
        }
        else if(choice == 0)
            break;
    }

    // Stack 2 input
    cout<<"\n[Stack 2]\n";

    while(true)
    {
        cout<<"\nChoose option:\n";
        cout<<"1 Push\n";
        cout<<"0 Done\n";
        cin>>choice;

        if(choice == 1)
        {
            cout<<"Enter value: ";
            cin>>value;

            if(!stack2.push(value))
            {
                cout<<"Stack full.\n";
                break;
            }
        }
        else if(choice == 0)
            break;
    }

    // Create Stack 3
    size = stack1.currentSize() + stack2.currentSize();

    stackLib::stk stack3;

    if(size > 100)
        stack3.initialize(size, size*2);
    else
        stack3.initialize(size);

    int i = stack1.currentSize();
    int j = stack2.currentSize();
    int count = 0;

    while(i>0 && j>0)
    {
        count++;

        if(count & 1)
        {
            value = stack1.pop();
            stack3.push(value);
            i--;
        }
        else
        {
            value = stack2.pop();
            stack3.push(value);
            j--;
        }
    }

    while(i>0)
    {
        value = stack1.pop();
        stack3.push(value);
        i--;
    }

    while(j>0)
    {
        value = stack2.pop();
        stack3.push(value);
        j--;
    }

    cout<<"\nFinal Stack 3:\n";
    stack3.display();

    return 0;
}
