#include "stack_mod.h"
#include<iostream>

int main()
{
	using std::cin; using std::cout; using std::endl;
	
	int size, limit, choice, value;

	stackLib::stk stack1;
	stack1.stack_arr=nullptr;

	stackLib::stk stack2;
	stack2.stack_arr=nullptr;

	cout<<"Initializing Stack 1\n"<<endl;
	cout<<"Enter initial size (-1 to set to default): ";
	cin>>size;
	if(size == 0 || size ==-1)
		stackLib::initialize(stack1);

	else 
	{
		cout<<"Enter maximum limit (-1 to set to default): ";
		cin>>limit;
		if(limit == 0 || limit == -1)
			stackLib::initialize(stack1, size);
		else stackLib::initialize(stack1, size, limit);
	}

	cout<<"Initializing Stack 2\n"<<endl;
	cout<<"Enter initial size (-1 to set to default): ";
	cin>>size;
	if(size == 0 || size ==-1) // Default
		stackLib::initialize(stack2);
	else 
	{
		cout<<"Enter maximum limit (-1 to set to default): ";
		cin>>limit;

		if(limit == 0 || limit == -1)
		    stackLib::initialize(stack2, size);
		
        else stackLib::initialize(stack2, size, limit);
	}

    //Creating stack 1

	cout<<"\n[Stack 1]\n";

	while(true)
	{
        cout<<"\nChoose option: "<<endl;
		cout<<"-------------------------------"<<endl;
		cout<<"\t[1]  Push"<<endl;
		cout<<"\t[0]  Go to stack 2\n"<<endl;
        cout<<"Select Option: ";
		cin>>choice;

		if(choice == 1) {
			cout<<"Enter value: "<<endl;
			cin>>value;
			if(!(stackLib::push(stack1, value)))
			{
				cout<<"\nGoing to stack 2."<<endl;
				break;
			}
		}

		else if(choice == 0)
		{
			cout<<"\nGoing to stack 2."<<endl;
			break;
		}

		else{
			cout<<"Enter valid option."<<endl;
		}

	}

    // Creating stack 2

	cout<<"\n[Stack 2]\n"<<endl;

	while(true)
	{
    	cout<<"\nChoose option: "<<endl;
		cout<<"-------------------------------"<<endl;
		cout<<"\t[1] Push"<<endl;
		cout<<"\t[0] Done\n"<<endl;
        cout<<"Select Option: ";
		cin>>choice;

		if(choice == 1){
			cout<<"Enter value: "<<endl;
			cin>>value;

			if(!(stackLib::push(stack2, value)))
			{
				cout<<"No more element can be pushed. Executing remaining part.\n"<<endl;
				break;
			}
		}

		else if(choice == 0)
		{
			break;
		}
		else{
			cout<<"Enter valid choice."<<endl;
		}
	}

	// Creating Stack 3
	
	size = stackLib::currentSize(stack1) + stackLib::currentSize(stack2);
	stackLib::stk stack3;
	stack3.stack_arr=nullptr;

	if(size > 100) stackLib::initialize(stack3, size, size*2);
	else stackLib::initialize(stack3, size);

	int i = stackLib::currentSize(stack1);
	int j= stackLib::currentSize(stack2);
	int count=0;
	
    while(i>0 && j>0)
	{
		count++;
		if((count & 1)!= 0) //Odd
		{
			value=stackLib::pop(stack1);
			stackLib::push(stack3, value);
			i--;
		}
		else //Even
		{
			value=stackLib::pop(stack2);
			stackLib::push(stack3, value);
			j--;
		}

	}

	while(i>0)
	{
		value=stackLib::pop(stack1);
		stackLib::push(stack3, value);
		i--;
	}

	while(j>0)
	{
		value=stackLib::pop(stack2);
		stackLib::push(stack3, value);
		j--;
	}


	stackLib::display(stack3);

    stackLib::release(stack1);
    stackLib::release(stack2);
    stackLib::release(stack3);

	return 0;
}

