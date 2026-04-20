#include <iostream>
#include "student_record.h"

using namespace std;
using namespace stdr;

void init(Student*& arr, int& capacity) 
{
    cout << "Enter the maximum number of students: ";
    while (!(cin >> capacity) || capacity <= 0) {
        cout << "Invalid input.";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    cin.ignore(1000, '\n');

    arr = new Student[capacity];
}


void release(Student*& arr) {
    if (arr != nullptr) {
        delete[] arr;
        arr = nullptr;
    }
}

int main() {
    Student* students = nullptr;
    int capacity = 0, count = 0, choice = -1;
    string filename;

    init(students, capacity);

    while (choice != 5){
        cout << "\nChoose an option: \n";
        cout << "\t1. Add Student Data\n";
        cout << "\t2. Print All Data\n";
        cout << "\t3. Write Data to File\n";
        cout << "\t4. Read Data from File\n";
        cout << "\t5. Exit\n";
        cout << "Enter choice: ";
        
        cin >> choice;
        cin.ignore();

        if(choice==5)
        {
            cout << "Exiting program...\n";
            break;
        }

        switch (choice) {
        case 1:

            if (count < capacity) {
                cout << "\nStudent " << (count + 1) << endl;
                ReadStudentData(students[count]);
                count++;
                cout << "Student data added.\n";
            } 
            else {
                cout << "\nError: Array is full. Cannot add more students.\n";
            }
            break;

        case 2:

            if (count == 0) {
                cout << "\nNo data available to print.\n";
            } 
            else {
                for (int i = 0; i < count; ++i) {
                    cout << "\n\tStudent " << (i + 1) <<endl;
                    PrintStudentData(students[i]);
                }
            }
            break;

        case 3:
            if (count == 0) {
                cout << "\nNo data to write.\n";
            } 
            else {
                cout << "Enter filename to write to: ";
                getline(cin, filename);
                
                bool write = true;
                for (int i = 0; i < count; i++) 
                {
                    if (!WriteDataToFile(students[i], filename)) 
                    {
                        write = false;
                        cout << "Failed to write student " << (i + 1) << endl;
                    }
                }
                if (write) cout << "Data written to " << filename << endl;
            }
            break;

        case 4:
            if (count < capacity) {
                cout << "Enter filename to read from: ";
                getline(cin, filename);

                if (ReadStudentDataFile(students, count, capacity, filename)) {
                    cout << "Data of " << count << " students read.\n";
                    count++;
                } 

                else {
                    cout << "Could not read from file.\n";
                }
            } 
            else {
                cout << "\nArray is full. Cannot save new data.\n";
            }
            break;

        default:
            cout << "Invalid option.\n";
        }

    }

    release(students);

    return 0;
}

