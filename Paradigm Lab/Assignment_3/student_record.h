#ifndef STUDENT_RECORD_H
#define STUDENT_RECORD_H

#include<iostream>
#include<string>
#include<fstream>

namespace stdr{

    class Student {
    private:
        std::string name;
        int age;
        std::string dept;
        int year;
        static int std_count;

    public:

        Student();

        static int getStudentCount();

        void ReadStudentData();
        bool WriteDataToFile(const std::string &filename) const;
        bool ReadStudentDataFile(const std::string &filename);
        void PrintStudentData() const;

        static bool ReadStudentDataFile(Student* arr, int &count, int capacity, const std::string& filename);
    };

}

#endif
