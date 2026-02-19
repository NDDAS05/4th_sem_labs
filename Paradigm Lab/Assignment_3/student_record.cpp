#include "student_record.h"

namespace stdr{

    int Student::std_count = 0;

    Student::Student()
    {
        std_count++;
    }

    int Student::getStudentCount()
    {
        return std_count;
    }

    void Student::ReadStudentData()
    {
        std::cout<<"Enter name: ";
        std::getline(std::cin, name);

        std::cout<<"Enter age: ";
        std::cin>>age;
        std::cin.ignore();

        std::cout<<"Enter department name: ";
        std::getline(std::cin, dept);

        std::cout<<"Enter year: ";
        std::cin>>year;
        std::cin.ignore();
    }

    bool Student::WriteDataToFile(const std::string &filename) const
    {
        std::ofstream file(filename, std::ios::app);
        if(!file) return false;

        file<<name<<std::endl;
        file<<age<<std::endl;
        file<<dept<<std::endl;
        file<<year<<std::endl;

        return true;
    }

    bool Student::ReadStudentDataFile(const std::string &filename)
    {
        std::ifstream f(filename);
        if(!f) return false;

        std::getline(f, name);
        f>>age;
        f.ignore();
        std::getline(f, dept);
        f>>year;
        f.ignore();

        return true;
    }

    bool Student::ReadStudentDataFile(Student* arr, int &count, int capacity, const std::string& filename)
    {
        std::ifstream f(filename);
        if(!f) return false;

        while(count < capacity && getline(f, arr[count].name)){
            f >> arr[count].age;
            f.ignore();
            getline(f, arr[count].dept);
            f >> arr[count].year;
            f.ignore();
            count++;
        }

        return true;
    }

    void Student::PrintStudentData() const
    {
        std::cout<<"Name      : "<<name<<std::endl;
        std::cout<<"Age       : "<<age<<std::endl;
        std::cout<<"Department: "<<dept<<std::endl;
        std::cout<<"Year      : "<<year<<std::endl;
    }

}
