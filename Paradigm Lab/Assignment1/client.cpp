#include <iostream>
#include "combined_mod.h"

using namespace std;
using namespace combined_mod;

int main()
{
    int op;

    while(true)
    {
        cout << "Choose an option:\n";
        cout << "\t1. Compare Strings\n";
        cout << "\t2. Find Largest among n integers\n";
        cout << "\t3. Linear Search\n";
        cout << "\t4. Print Array in Reverse\n";
        cout << "\t5. Check Palindrome\n";
        cout << "\t6. Replace character in string\n";
        cout << "\t7. Sum of array elements\n";
        cout << "\t8. Smallest character in string\n";
        cout << "\t9. Exit\n";

        cout << "Enter option: ";
        cin >> op;

        if(op == 9) break;

        switch(op)
        {
            case 1: {
                char s1[50], s2[50];
                cout << "Enter string 1: ";
                cin >> s1;
                cout << "Enter string 2: ";
                cin >> s2;
                cout << "Result: " << string_comp(s1, s2) << endl;
                break;
            }

            case 2: {
                int size;
                cout << "Enter size: ";
                cin >> size;
                int* arr = init(size);
                for(int i=0;i<size;i++) cin >> arr[i];
                cout << "Max: " << max_num(arr, size) << endl;
                arr = free_arr(arr);
                break;
            }

            case 3: {
                int size, key;
                cout << "Enter size: ";
                cin >> size;
                int* arr = init(size);
                for(int i=0;i<size;i++) cin >> arr[i];
                cout << "Enter element to search: ";
                cin >> key;
                cout << (lin_search(arr, size, key) ? "Found\n" : "Not Found\n");
                arr = free_arr(arr);
                break;
            }

            case 4: {
                int size;
                cout << "Enter size: ";
                cin >> size;
                int* arr = init(size);
                cout<<"Enter elements: \n";
                for(int i=0;i<size;i++) cin >> arr[i];
                print_reverse(arr, size);
                cout << endl;
                arr = free_arr(arr);
                break;
            }

            case 5: {
                char str[50];
                cout << "Enter string: ";
                cin >> str;
                cout << (if_palindrome(str, 0, strlen(str)-1) ?
                        "Palindrome\n" : "Not Palindrome\n");
                break;
            }

            case 6: {
                char str[50], c1, c2;
                cout << "Enter string: ";
                cin >> str;
                cout << "Enter char to replace: ";
                cin >> c1;
                cout << "Enter replacement char: ";
                cin >> c2;
                replace(str, c1, c2);
                cout << "Modified string: " << str << endl;
                break;
            }

            case 7: {
                int size;
                cout << "Enter size: ";
                cin >> size;
                int* arr = init(size);
                for(int i=0;i<size;i++) cin >> arr[i];
                cout << "Sum: " << sumArr(arr, size, 0) << endl;
                arr = free_arr(arr);
                break;
            }

            case 8: {
                char str[50];
                cout << "Enter string: ";
                cin >> str;
                cout << "Smallest char: " << min_char(str, strlen(str)) << endl;
                break;
            }

            default:
                cout << "Invalid option\n";
        }
    }

    return 0;
}
