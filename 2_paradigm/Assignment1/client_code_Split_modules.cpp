#include <iostream>
#include <cstring>

#include "array_mod.h"
#include "string_mod.h"

using namespace std;

int main()
{
    int choice;

    while (true)
    {
        cout << "\n Choose an option: \n";
        cout << "\t1. Compare two strings\n";
        cout << "\t2. Find maximum in array\n";
        cout << "\t3. Linear search in array\n";
        cout << "\t4. Print array in reverse order\n";
        cout << "\t5. Check palindrome string\n";
        cout << "\t6. Replace character in string\n";
        cout << "\t7. Sum of array elements\n";
        cout << "\t8. Smallest character in string\n";
        cout << "\t9. Exit\n";
        cout << "Enter choice: ";

        cin >> choice;

        if (choice == 9)
        {
            cout << "Exiting...\n";
            break;
        }

        switch (choice)
        {
            case 1:
            {
                char s1[50], s2[50];
                cout << "Enter string 1: ";
                cin >> s1;
                cout << "Enter string 2: ";
                cin >> s2;

                int res = string_mod::string_comp(s1, s2);
                cout << "Result: " << res << endl;
                break;
            }

            case 2:
            {
                int size;
                cout << "Enter array size: ";
                cin >> size;

                int* arr = array_mod::init(size);
                cout << "Enter elements:\n";
                for (int i = 0; i < size; i++)
                    cin >> arr[i];

                cout << "Maximum value: "
                     << array_mod::max_num(arr, size) << endl;

                arr = array_mod::free_arr(arr);
                break;
            }

            case 3:
            {
                int size, key;
                cout << "Enter array size: ";
                cin >> size;

                int* arr = array_mod::init(size);
                cout << "Enter elements:\n";
                for (int i = 0; i < size; i++)
                    cin >> arr[i];

                cout << "Enter element to search: ";
                cin >> key;

                if (array_mod::lin_search(arr, size, key))
                    cout << "Element found\n";
                else
                    cout << "Element not found\n";

                arr = array_mod::free_arr(arr);
                break;
            }

            case 4:
            {
                int size;
                cout << "Enter array size: ";
                cin >> size;

                int* arr = array_mod::init(size);
                cout << "Enter elements:\n";
                for (int i = 0; i < size; i++)
                    cin >> arr[i];

                cout << "Reverse order: ";
                array_mod::print_reverse(arr, size);
                cout << endl;

                arr = array_mod::free_arr(arr);
                break;
            }

            case 5:
            {
                char str[50];
                cout << "Enter string: ";
                cin >> str;

                if (string_mod::if_palindrome(str, 0, strlen(str) - 1))
                    cout << "Palindrome string\n";
                else
                    cout << "Not a palindrome\n";
                break;
            }

            case 6:
            {
                char str[50], c1, c2;
                cout << "Enter string: ";
                cin >> str;
                cout << "Enter character to replace: ";
                cin >> c1;
                cout << "Enter replacement character: ";
                cin >> c2;

                string_mod::replace(str, c1, c2);
                cout << "Modified string: " << str << endl;
                break;
            }

            case 7:
            {
                int size;
                cout << "Enter array size: ";
                cin >> size;

                int* arr = array_mod::init(size);
                cout << "Enter elements:\n";
                for (int i = 0; i < size; i++)
                    cin >> arr[i];

                cout << "Sum of elements: "
                     << array_mod::sumArr(arr, size, 0) << endl;

                arr = array_mod::free_arr(arr);
                break;
            }

            case 8:
            {
                char str[50];
                cout << "Enter string: ";
                cin >> str;

                cout << "Smallest character: "
                     << string_mod::min_char(str, strlen(str)) << endl;
                break;
            }

            default:
                cout << "Invalid choice\n";
        }
    }

    return 0;
}
