#include<iostream>
#include<string>

template<typename T>
void swap(T &a, T &b)
{
    T temp=a;
    a=b;
    b=temp;
}

struct Student{
    std::string enrollment_no;
    std::string name;
};

int main()
{
    using std::cout;
    using std::cin;
    using std::endl;


    int choice;
    bool run=true;

    while(run)
    {
        cout<<"Select one option."<<endl;
        cout<<"\n\t[1] Swap integers"<<endl;
        cout<<"\t[2] Swap short"<<endl;
        cout<<"\t[3] Swap floats"<<endl;
        cout<<"\t[4] Swap doubles"<<endl;
        cout<<"\t[5] Swap structures\n"<<endl;
        cout<<"\t[0] Exit"<<endl;
        cout<<"-------------------------------"<<endl<<"Choose option: ";
        cin>>choice;

        switch(choice)
        {
            case 1: {
                int num1, num2;
                cout<<"Enter integer 1: ";
                cin>>num1;
                
                cout<<"Enter integer 2: ";
                cin>>num2;

                cout<<"Input given: "<<num1<<" "<<num2<<endl;
                swap(num1, num2);
                cout<<"After swapping: "<<num1<<" "<<num2<<endl;
                break;
            }

            case 2: {
                short num1, num2;
                cout<<"Enter short 1: ";
                cin>>num1;
                
                cout<<"Enter short 2: ";
                cin>>num2;

                cout<<"Input given: "<<num1<<" "<<num2<<endl;
                swap(num1, num2);
                cout<<"After swapping: "<<num1<<" "<<num2<<endl;
                break;
            }

            case 3: {
                float num1, num2;
                cout<<"Enter float number 1: ";
                cin>>num1;
                
                cout<<"Enter float number 2: ";
                cin>>num2;

                cout<<"Input given: "<<num1<<" "<<num2<<endl;
                swap(num1, num2);
                cout<<"After swapping: "<<num1<<" "<<num2<<endl;
                break;
            }

            case 4: {
                double num1, num2;
                cout<<"Enter double 1: ";
                cin>>num1;
                
                cout<<"Enter double 2: ";
                cin>>num2;

                cout<<"Input given: "<<num1<<" "<<num2<<endl;
                swap(num1, num2);
                cout<<"After swapping: "<<num1<<" "<<num2<<endl;
                break;
            }
            case 5: {
                Student s1, s2;
                cin.ignore();
                cout<<"Entering Data for Student Structure 1"<<endl;
                cout<<"\nEnter enrollment number: ";
                std::getline(cin, s1.enrollment_no);
                cout<<"Enter name: ";
                std::getline(cin, s1.name);

                cout<<"Entering Data for Student Structure 2"<<endl;
                cout<<"\nEnter enrollment number: ";
                std::getline(cin, s2.enrollment_no);
                cout<<"Enter name: ";
                std::getline(cin, s2.name);

                swap(s1, s2);

                cout<<"After swapping: "<<endl;
                cout<<"Student 1:\nName: "<<s1.name<<endl<<"Enrollment no. "<<s1.enrollment_no<<endl;
                cout<<"Student 2:\nName: "<<s2.name<<endl<<"Enrollment no. "<<s2.enrollment_no<<endl;

                break;
            }
            case 0:
                cout<<"Exiting program..."<<endl;
                run=false;
                break;
            default:
                cout<<"Enter valid option."<<endl;
        }
    }
    return 0;
}