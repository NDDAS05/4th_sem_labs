#include <iostream>
#include <climits>
#include <cstdlib>

namespace stackLib {



template <typename T>
struct stk {
    T* stack_arr;
    int capacity;
    int MaxLimit;
    int top;
};


template <typename T>
void initialize(stk<T>& s, int size = 2, int limit = 10) {
    s.capacity = size;
    s.MaxLimit = limit;
    s.top = -1;
    s.stack_arr = new T[s.capacity];
}

template <typename T>
void release(stk<T>& s) {
    delete[] s.stack_arr;
    s.stack_arr = nullptr;
    s.top = -1;
}

template <typename T>
int inflate(stk<T>& s) {
    if (s.capacity >= s.MaxLimit)
        return 0;

    int newCap = s.capacity * 2;
    if (newCap > s.MaxLimit)
        newCap = s.MaxLimit;

    std::cout << "[Inflating stack]\n";

    T* newArr = new T[newCap];

    for (int i = 0; i <= s.top; i++)
        newArr[i] = s.stack_arr[i];

    delete[] s.stack_arr;
    s.stack_arr = newArr;
    s.capacity = newCap;

    return 1;
}

template <typename T>
int push(stk<T>& s, const T& value) {
    if (s.top == s.capacity - 1)
        if (!inflate(s)) {
            std::cout << "Stack Overflow.\n";
            return 0;
        }

    s.stack_arr[++s.top] = value;
    return 1;
}

template <typename T>
int push(stk<T>& s, T* arr, int count) {
    for (int i = 0; i < count; i++)
        if (!push(s, arr[i]))
            return 0;
    return 1;
}

template <typename T>
T pop(stk<T>& s) {
    if (s.top == -1) {
        std::cout << "Stack Underflow.\n";
        return T();
    }
    return s.stack_arr[s.top--];
}

template <typename T>
void display(stk<T>& s) {
    std::cout << "[ ";
    for (int i = 0; i <= s.top; i++)
        std::cout << s.stack_arr[i] << " ";
    std::cout << "]\n";
}

} // namespace stackLib

struct Student {
    int roll;
    float marks;
};


std::ostream& operator<<(std::ostream& os, const Student& s) {
    os << "(Roll: " << s.roll << ", Marks: " << s.marks << ")";
    return os;
}


int main() {

    int ch;

    std::cout << "Select Stack Type:\n";
    std::cout << "1. Integer\n";
    std::cout << "2. Float\n";
    std::cout << "3. Student Struct\n";
    std::cout << "Enter choice: ";
    std::cin >> ch;


    if (ch == 1) {

        stackLib::stk<int> mystack;
        mystack.stack_arr = nullptr;

        int choice, value, size, limit;

        while (true) {

            if (mystack.stack_arr == nullptr) {

                std::cout << "Enter 1 to create a stack. 0 to exit.\n";
                std::cin >> choice;

                if (choice == 0)
                    std::exit(1);

                std::cout << "Enter size (-1 default): ";
                std::cin >> size;

                if (size <= 0)
                    stackLib::initialize(mystack);
                else {
                    std::cout << "Enter maximum capacity (-1 default): ";
                    std::cin >> limit;
                    if (limit <= 0)
                        stackLib::initialize(mystack, size);
                    else
                        stackLib::initialize(mystack, size, limit);
                }

                while (true) {

                    std::cout << "\n1.Push\n2.Push multiple elements\n3.Pop\n4.Print\n5.Current size\n6.Max capacity\n7.Clear & exit\n";
                    std::cin >> choice;

                    if (choice == 7) {
                        stackLib::release(mystack);
                        break;
                    }

                    switch (choice) {

                    case 1:
                        std::cout << "Enter element: ";
                        std::cin >> value;
                        stackLib::push(mystack, value);
                        break;

                    case 2: {
                        std::cout << "Enter count: ";
                        std::cin >> value;
                        int* arr = new int[value];
                        for (int i = 0; i < value; i++)
                            std::cin >> arr[i];
                        stackLib::push(mystack, arr, value);
                        delete[] arr;
                        break;
                    }

                    case 3:
                        std::cout << "Popped: "
                                  << stackLib::pop(mystack) << std::endl;
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
                        std::cout << "Invalid choice.\n";
                    }
                }
            }
        }
    }


    else if (ch == 2) {

        stackLib::stk<float> mystack;
        stackLib::initialize(mystack);

        stackLib::push(mystack, 1.1f);
        stackLib::push(mystack, 2.2f);
        stackLib::display(mystack);

        stackLib::release(mystack);
    }

    else if (ch == 3) {

        stackLib::stk<Student> mystack;
        stackLib::initialize(mystack);

        Student s1 = {1, 85.5};
        Student s2 = {2, 91.2};

        stackLib::push(mystack, s1);
        stackLib::push(mystack, s2);

        stackLib::display(mystack);

        stackLib::release(mystack);
    }

    else {
        std::cout << "Invalid type selection.\n";
    }

    return 0;
}
