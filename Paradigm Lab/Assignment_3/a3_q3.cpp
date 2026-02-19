#include <iostream>
using namespace std;

struct Student
{
    int id;
    float marks;
};

ostream& operator<<(ostream& os, const Student& s)
{
    os << "[ID=" << s.id << ", Marks=" << s.marks << "]";
    return os;
}


template<class T>
class GrowingStack
{
private:

    T* stack_arr;
    int top;
    int capacity;
    int maxLimit;

    bool inflate()
    {
        if(capacity >= maxLimit)
            return false;

        int newCapacity = capacity * 2;

        if(newCapacity > maxLimit)
            newCapacity = maxLimit;

        T* newArr = new T[newCapacity];

        for(int i = 0; i <= top; i++)
            newArr[i] = stack_arr[i];

        delete[] stack_arr;

        stack_arr = newArr;
        capacity = newCapacity;

        return true;
    }

public:

    GrowingStack(int initialSize = 10, int maxLimit = 100)
    {
        this->capacity = initialSize;
        this->maxLimit = maxLimit;
        this->top = -1;

        stack_arr = new T[capacity];
    }

    GrowingStack(const GrowingStack& other)
    {
        capacity = other.capacity;
        maxLimit = other.maxLimit;
        top = other.top;

        stack_arr = new T[capacity];

        for(int i = 0; i <= top; i++)
            stack_arr[i] = other.stack_arr[i];
    }

    GrowingStack& operator=(const GrowingStack& other)
    {
        if(this != &other)
        {
            delete[] stack_arr;

            capacity = other.capacity;
            maxLimit = other.maxLimit;
            top = other.top;

            stack_arr = new T[capacity];

            for(int i = 0; i <= top; i++)
                stack_arr[i] = other.stack_arr[i];
        }

        return *this;
    }

    ~GrowingStack()
    {
        delete[] stack_arr;
    }

    bool push(const T& value)
    {
        if(top == capacity - 1)
        {
            if(!inflate())
                return false;
        }

        stack_arr[++top] = value;
        return true;
    }

    T pop()
    {
        if(top == -1)
        {
            cout<<"Stack Empty\n";
            return T();
        }

        return stack_arr[top--];
    }

    void display() const
    {
        if(top == -1)
        {
            cout<<"Stack Empty\n";
            return;
        }

        cout<<"Stack contents:\n";

        for(int i = top; i >= 0; i--)
            cout<<stack_arr[i]<<endl;
    }

    int size() const
    {
        return top + 1;
    }

    void release()
    {
        delete[] stack_arr;
        stack_arr = new T[capacity];
        top = -1;
    }

};

template<class T>
void operateStack()
{
    GrowingStack<T>* stack1 = nullptr;
    GrowingStack<T>* stack2 = nullptr;

    int choice;
    int size, limit;

    while(true)
    {
        cout<<"\nChoose an option:\n";

        cout<<"1. Create Stack 1\n";
        cout<<"2. Push Stack 1\n";
        cout<<"3. Display Stack 1\n";
        cout<<"4. Copy Constructor (Stack2 from Stack1)\n";
        cout<<"5. Assignment Operator (Stack2 = Stack1)\n";
        cout<<"6. Display Stack 2\n";
        cout<<"7. Release Stack 1\n";
        cout<<"8. Release Stack 2\n";
        cout<<"0. Exit\n";

        cout<<"Enter choice: ";
        cin>>choice;


        switch(choice)
        {

            case 1:
                if(stack1)
                    delete stack1;

                cout<<"Enter size: ";
                cin>>size;
                cout<<"Enter max limit: ";
                cin>>limit;
                stack1 = new GrowingStack<T>(size, limit);
                cout<<"Stack1 created\n";
                break;

            case 2:
                if(!stack1)
                {
                    cout<<"Create stack1 first\n";
                    break;
                }

                T value;
                cout<<"Enter value: ";
                cin>>value;
                stack1->push(value);
                break;

            case 3:
                if(stack1)
                    stack1->display();
                break;

            case 4:
                if(!stack1)
                {
                    cout<<"Create stack1 first\n";
                    break;
                }

                if(stack2)
                    delete stack2;

                stack2 = new GrowingStack<T>(*stack1);
                cout<<"Copy constructor used. Stack2 created.\n";
                break;

            case 5:
                if(!stack1)
                {
                    cout<<"Create stack1 first\n";
                    break;
                }

                if(!stack2)
                    stack2 = new GrowingStack<T>;

                *stack2 = *stack1;
                cout<<"Assignment operator used.\n";
                break;

            case 6:
                if(stack2)
                    stack2->display();
                else
                    cout<<"Stack2 not created\n";

                break;

            case 7:
                if(stack1)
                {
                    stack1->release();
                    cout<<"Stack1 released\n";
                }

                break;

            case 8:
                if(stack2)
                {
                    stack2->release();
                    cout<<"Stack2 released\n";
                }

                break;

            case 0:

                delete stack1;
                delete stack2;
                return;
        }
    }
}

int main()
{
    int choice;

    while(true)
    {
        cout<<"\nChoose data type:\n";

        cout<<"1. int\n";
        cout<<"2. short\n";
        cout<<"3. float\n";
        cout<<"4. double\n";
        cout<<"5. Student\n";
        cout<<"0. Exit\n";

        cin>>choice;


        switch(choice)
        {

            case 1: operateStack<int>(); break;

            case 2: operateStack<short>(); break;

            case 3: operateStack<float>(); break;

            case 4: operateStack<double>(); break;

            case 5: operateStack<Student>(); break;

            case 0: return 0;
        }
    }
}
