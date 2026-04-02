#ifndef STUDENT_RECORD_H
#define STUDENT_RECORD_H

#include<iostream>
#include<string>
#include<fstream>

namespace stdr{
    struct Student {
        std::string name;
        int age;
        std::string dept;
        int year;
    };

    void ReadStudentData(Student &s);
    bool ReadStudentDataFile(Student &s, const std::string &filename);
    bool ReadStudentDataFile(Student* arr, int &count, int &capacity, const std::string& filename);
    bool WriteDataToFile(const Student &s, const std::string &filename);
    void PrintStudentData(const Student &s);
    
}

#endif