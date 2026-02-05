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
void display(const stk<T>& s) {
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

    while (true) {

        std::cout << "\nSelect Stack Type:\n";
        std::cout << "1. Integer\n";
        std::cout << "2. Float\n";
        std::cout << "3. Student Struct\n";
        std::cout << "4. char*\n";
        std::cout << "5. std::string\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> ch;

        if (ch == 0)
            return 0;

        int size, limit;

        std::cout << "Enter initial size (-1 default): ";
        std::cin >> size;

        std::cout << "Enter maximum capacity (-1 default): ";
        std::cin >> limit;


        if (ch == 1) {

            stackLib::stk<int> s;
            stackLib::initialize(s,
                                 (size <= 0 ? 2 : size),
                                 (limit <= 0 ? 10 : limit));

            int choice, value;

            while (true) {
                std::cout << "\n1.Push\n2.Pop\n3.Display\n4.Clear & Back\n";
                std::cin >> choice;

                if (choice == 4) {
                    stackLib::release(s);
                    break;
                }

                switch (choice) {
                case 1:
                    std::cout << "Enter integer: ";
                    std::cin >> value;
                    stackLib::push(s, value);
                    break;
                case 2:
                    std::cout << "Popped: "
                              << stackLib::pop(s) << std::endl;
                    break;
                case 3:
                    stackLib::display(s);
                    break;
                }
            }
        }


        else if (ch == 2) {

            stackLib::stk<float> s;
            stackLib::initialize(s,
                                 (size <= 0 ? 2 : size),
                                 (limit <= 0 ? 10 : limit));

            int choice;
            float value;

            while (true) {
                std::cout << "\n1.Push\n2.Pop\n3.Display\n4.Clear & Back\n";
                std::cin >> choice;

                if (choice == 4) {
                    stackLib::release(s);
                    break;
                }

                switch (choice) {
                case 1:
                    std::cout << "Enter float: ";
                    std::cin >> value;
                    stackLib::push(s, value);
                    break;
                case 2:
                    std::cout << "Popped: "
                              << stackLib::pop(s) << std::endl;
                    break;
                case 3:
                    stackLib::display(s);
                    break;
                }
            }
        }


        else if (ch == 3) {

            stackLib::stk<Student> s;
            stackLib::initialize(s,
                                 (size <= 0 ? 2 : size),
                                 (limit <= 0 ? 10 : limit));

            int choice;
            Student temp;

            while (true) {
                std::cout << "\n1.Push\n2.Pop\n3.Display\n4.Clear & Back\n";
                std::cin >> choice;

                if (choice == 4) {
                    stackLib::release(s);
                    break;
                }

                switch (choice) {
                case 1:
                    std::cout << "Enter roll: ";
                    std::cin >> temp.roll;
                    std::cout << "Enter marks: ";
                    std::cin >> temp.marks;
                    stackLib::push(s, temp);
                    break;
                case 2:
                    temp = stackLib::pop(s);
                    std::cout << "Popped: " << temp << std::endl;
                    break;
                case 3:
                    stackLib::display(s);
                    break;
                }
            }
        }


        else if (ch == 4) {

            stackLib::stk<char*> s;
            stackLib::initialize(s,
                                 (size <= 0 ? 2 : size),
                                 (limit <= 0 ? 10 : limit));

            int choice;
            char buffer[100];

            while (true) {
                std::cout << "\n1.Push\n2.Pop\n3.Display\n4.Clear & Back\n";
                std::cin >> choice;

                if (choice == 4) {
                    stackLib::release(s);
                    break;
                }

                switch (choice) {
                case 1:
                    std::cout << "Enter string: ";
                    std::cin >> buffer;
                    s.stack_arr[++s.top] = buffer;
                    break;

                case 2:
                    std::cout << "Popped: "
                              << stackLib::pop(s) << std::endl;
                    break;

                case 3:
                    stackLib::display(s);
                    break;
                }
            }
        }


        else if (ch == 5) {

            stackLib::stk<std::string> s;
            stackLib::initialize(s,
                                 (size <= 0 ? 2 : size),
                                 (limit <= 0 ? 10 : limit));

            int choice;
            std::string value;

            while (true) {
                std::cout << "\n1.Push\n2.Pop\n3.Display\n4.Clear & Back\n";
                std::cin >> choice;

                if (choice == 4) {
                    stackLib::release(s);
                    break;
                }

                switch (choice) {
                case 1:
                    std::cin.ignore();
                    std::cout << "Enter string: ";
                    std::getline(std::cin,value);
                    stackLib::push(s, value);
                    std::cin.ignore();
                    break;
                case 2:
                    std::cout << "Popped: "
                              << stackLib::pop(s) << std::endl;
                    break;
                case 3:
                    stackLib::display(s);
                    break;
                }
            }
        }

        else {
            std::cout << "Invalid choice.\n";
        }
    }

    return 0;
}