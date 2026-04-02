#include "student_record.h"

namespace stdr{

    void ReadStudentData(Student &s)
    {
	    std::cout<<"Enter name: ";
	    std::getline(std::cin, s.name);

    	std::cout<<"Enter age: ";
    	std::cin>>s.age;
    	std::cin.ignore();

    	std::cout<<"Enter department name: ";
    	std::getline(std::cin, s.dept);

    	std::cout<<"Enter year: ";
    	std::cin>>s.year;
    	std::cin.ignore();
    }

    bool WriteDataToFile(const Student &s, const std::string &filename)
    {
	    std::ofstream file(filename, std::ios::app);
	    if(!file) return false;

	    file<<s.name<<std::endl;
	    file<<s.age<<std::endl;
	    file<<s.dept<<std::endl;
	    file<<s.year<<std::endl;
	
	    file.close();

	    return true;
    }

    bool ReadStudentDataFile(Student &s, const std::string &filename)
    {
	    std::ifstream f(filename);
	    if(!f) return false;

	    std::getline(f, s.name);
	    f>>s.age;
	    f.ignore();
	    std::getline(f, s.dept);
	    f>>s.year;
	    f.ignore();

	    f.close();

	    return true;
    }

	bool ReadStudentDataFile(Student* arr, int &count, int &capacity, const std::string& filename)
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

		f.close();
		return true;
	}

    void PrintStudentData(const Student &s)
    {
	    std::cout<<"Name	  : "<<s.name<<std::endl;
	    std::cout<<"Age       : "<<s.age<<std::endl;
	    std::cout<<"Department: "<<s.dept<<std::endl;
	    std::cout<<"Year      : "<<s.year<<std::endl;
    }
}