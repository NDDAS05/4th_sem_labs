#include <iostream>
#include <climits>
#include <string>

using namespace std;

namespace stackLib {

    class stk {
    private:
        int *stack_arr;
        int top;
        int capacity;
        int MaxLimit;

        static int active_stack_count;
        static int MAX_ALLOWED_STACKS;

        int inflate();

        stk();
        stk(const stk &other);

    public:
        ~stk();
        stk& operator=(const stk &other);

        static void setMaxAllowedStacks(int limit);
        static stk* createStack();
        static stk* cloneStack(const stk &other);
        static int getActiveStackCount();
        static int getMaxAllowedStacks();

        void initialize(int initialSize = 10, int MaxLimit = 100);
        int push(int elem);
        int push(int *arr, int count);
        int pop();
        bool isEmpty() const;
        int currentSize() const;
        int getMaxSize() const;
        void display() const;
    };

    int stk::active_stack_count = 0;
    int stk::MAX_ALLOWED_STACKS = 0;

    void stk::setMaxAllowedStacks(int limit) {
        MAX_ALLOWED_STACKS = limit;
    }

    stk* stk::createStack() {
        if (active_stack_count >= MAX_ALLOWED_STACKS) {
            cout << "\nMaximum stack limit (" << MAX_ALLOWED_STACKS << ") reached.\n";
            return nullptr;
        }
        active_stack_count++;
        return new stk();
    }

    stk* stk::cloneStack(const stk &other) {
        if (active_stack_count >= MAX_ALLOWED_STACKS) {
            cout << "\nMaximum stack limit (" << MAX_ALLOWED_STACKS << ") reached.\n";
            return nullptr;
        }
        active_stack_count++;
        return new stk(other);
    }

    int stk::getActiveStackCount() {
        return active_stack_count;
    }

    int stk::getMaxAllowedStacks() {
        return MAX_ALLOWED_STACKS;
    }

    stk::stk() {
        stack_arr = nullptr;
        top = -1;
        capacity = 0;
        MaxLimit = 0;
    }

    stk::stk(const stk &other) {
        capacity = other.capacity;
        MaxLimit = other.MaxLimit;
        top = other.top;

        if (capacity > 0) {
            stack_arr = new int[capacity];
            for (int i = 0; i <= top; i++)
                stack_arr[i] = other.stack_arr[i];
        } else {
            stack_arr = nullptr;
        }
    }

    stk& stk::operator=(const stk &other) {
        if (this == &other)
            return *this;

        delete[] stack_arr;

        capacity = other.capacity;
        MaxLimit = other.MaxLimit;
        top = other.top;

        if (capacity > 0) {
            stack_arr = new int[capacity];
            for (int i = 0; i <= top; i++)
                stack_arr[i] = other.stack_arr[i];
        } else {
            stack_arr = nullptr;
        }

        return *this;
    }

    stk::~stk() {
        delete[] stack_arr;
        active_stack_count--;
    }

    void stk::initialize(int initialSize, int MaxLimit) {
        delete[] stack_arr;

        this->capacity = initialSize;
        this->MaxLimit = MaxLimit;
        this->top = -1;

        stack_arr = new int[capacity];
    }

    bool stk::isEmpty() const {
        return top == -1;
    }

    int stk::currentSize() const {
        return top + 1;
    }

    int stk::getMaxSize() const {
        return MaxLimit;
    }

    int stk::inflate() {
        if (capacity >= MaxLimit)
            return 0;

        int newCap = capacity * 2;
        if (newCap > MaxLimit)
            newCap = MaxLimit;

        int *newArr = new int[newCap];
        for (int i = 0; i <= top; i++)
            newArr[i] = stack_arr[i];

        delete[] stack_arr;

        stack_arr = newArr;
        capacity = newCap;

        return 1;
    }

    int stk::push(int elem) {
        if(stack_arr == nullptr) 
            return 0;

        if (top == capacity - 1) {
            if (!inflate()) {
                cout << "Stack overflowed.\n";
                return 0;
            }
        }
        stack_arr[++top] = elem;
        return 1;
    }

    int stk::push(int *arr, int count) {
        for (int i = 0; i < count; i++)
            if (!push(arr[i]))
                return 0;
        return 1;
    }

    int stk::pop() {
        if (isEmpty()) {
            cout << "Stack underflowed.\n";
            return INT_MIN;
        }
        return stack_arr[top--];
    }

    void stk::display() const {
        if (stack_arr == nullptr) {
            cout << "Stack not initialized.\n";
            return;
        }
        cout << "[ ";
        for (int i = 0; i <= top; i++)
            cout << stack_arr[i] << " ";
        cout << "]\n";
    }
}

using namespace stackLib;

int main() {
    int max_slots;
    
    cout << "Enter the maximum number of stacks allowed: ";
    cin >> max_slots;
    
    if (max_slots <= 0) {
        cout << "Invalid number of stacks. Exiting program.\n";
        return 1;
    }

    stk::setMaxAllowedStacks(max_slots);

    stk** myStacks = new stk*[max_slots];
    for (int i = 0; i < max_slots; i++) {
        myStacks[i] = nullptr;
    }
    
    int active_index = -1;
    int choice;

    while (true) {
        cout << "[ Active: " << stk::getActiveStackCount() << "/" << stk::getMaxAllowedStacks() << " ]\n";
        cout << "-----------------------------------------\n";
        
        if (active_index != -1 && myStacks[active_index] != nullptr) {
            cout << "[Currently on Stack " << active_index + 1 << "]\n";
        } else {
            cout << "[No Stack Selected]\n";
        }
        
        cout << "-----------------------------------------\n";
        cout << "1. Create a New Stack\n";
        cout << "2. Select an Existing Stack\n";
        cout << "3. Initialize Current Stack (Set Capacity)\n";
        cout << "4. Push Single Element\n";
        cout << "5. Push Array of Elements\n";
        cout << "6. Pop Element\n";
        cout << "7. Display Current Stack\n";
        cout << "8. Delete/Destroy Current Stack\n";
        cout << "9. Exit System\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 9) {
            cout << "Cleaning up resources...\n";
            for (int i = 0; i < max_slots; i++) {
                if (myStacks[i] != nullptr) {
                    delete myStacks[i];
                }
            }
            delete[] myStacks;
            cout << "Exiting...\n";
            break;
        }

        switch (choice) {
            case 1: {
                stk* newStack = stk::createStack();
                if (newStack != nullptr) {
                    for (int i = 0; i < max_slots; i++) {
                        if (myStacks[i] == nullptr) {
                            myStacks[i] = newStack;
                            active_index = i;
                            cout << "Successfully created and selected Stack " << i + 1 << ".\n";
                            break;
                        }
                    }
                }
                break;
            }

            case 2: {
                cout << "\nAvailable Stacks:\n";
                bool found = false;
                for (int i = 0; i < max_slots; i++) {
                    if (myStacks[i] != nullptr) {
                        cout << " - Stack " << i + 1 << "\n";
                        found = true;
                    }
                }
                if (!found) {
                    cout << "No stacks currently exist.\n";
                    break;
                }
                
                int slot;
                cout << "Select stack number: ";
                cin >> slot;
                if (slot > 0 && slot <= max_slots && myStacks[slot - 1] != nullptr) {
                    active_index = slot - 1;
                    cout << "Stack " << slot << " is now selected.\n";
                } else {
                    cout << "Invalid stack.\n";
                }
                break;
            }

            case 3: {
                if (active_index == -1 || myStacks[active_index] == nullptr) {
                    cout << "Please select or create a stack first (Option 1 or 2).\n";
                    break;
                }
                int initSize, maxLim;
                cout << "Enter Initial Size: ";
                cin >> initSize;
                cout << "Enter Maximum Limit: ";
                cin >> maxLim;
                myStacks[active_index]->initialize(initSize, maxLim);
                cout << "Stack initialized.\n";
                break;
            }

            case 4: {
                if (active_index == -1 || myStacks[active_index] == nullptr) {
                    cout << "Select or create a stack first.\n";
                    break;
                }
                if (myStacks[active_index]->getMaxSize() == 0) {
                    cout << "Stack is not initialized.\n";
                    break;
                }
                
                int val;
                cout << "Enter value to push: ";
                cin >> val;
                if (myStacks[active_index]->push(val)) {
                    cout << "Pushed successfully.\n";
                } else {
                    cout << "Push failed (Stack might be full).\n";
                }
                break;
            }

            case 5: {
                if (active_index == -1 || myStacks[active_index] == nullptr) {
                    cout << "Please select or create a stack first.\n";
                    break;
                }
                if (myStacks[active_index]->getMaxSize() == 0) {
                    cout << "Stack is not initialized.\n";
                    break;
                }
                
                int count;
                cout << "How many elements to push? ";
                cin >> count;
                if (count <= 0) break;
                
                int* arr = new int[count];
                cout << "Enter " << count << " space-separated integers: ";
                for (int i = 0; i < count; i++) {
                    cin >> arr[i];
                }
                
                if (myStacks[active_index]->push(arr, count)) {
                    cout << "Array pushed successfully.\n";
                } else {
                    cout << "Push incomplete (Capacity reached).\n";
                }
                delete[] arr;
                break;
            }

            case 6: {
                if (active_index == -1 || myStacks[active_index] == nullptr) {
                    cout << "Select or create a stack first.\n";
                    break;
                }
                if (myStacks[active_index]->getMaxSize() == 0) {
                    cout << "Stack is not initialized.\n";
                    break;
                }
                
                int val = myStacks[active_index]->pop();
                if (val != INT_MIN) {
                    cout << "Popped value: " << val << "\n";
                }
                break;
            }

            case 7: {
                if (active_index == -1 || myStacks[active_index] == nullptr) {
                    cout << "Please select or create a stack first.\n";
                    break;
                }
                cout << "Stack contents: ";
                myStacks[active_index]->display();
                break;
            }

            case 8: {
                if (active_index == -1 || myStacks[active_index] == nullptr) {
                    cout << "Please select or create a stack first.\n";
                    break;
                }
                delete myStacks[active_index];
                myStacks[active_index] = nullptr;
                cout << "Stack " << active_index + 1 << " destroyed!\n";
                active_index = -1;
                break;
            }

            default:
                cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}