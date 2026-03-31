#include <cstring>
#include <iostream>
using std::cin, std::cout, std::endl;

/*
      ----Member----
      |           \
    Empployee   Trainee
    1. Dev
    2. SysAdmin
*/

class Member {
  char *name;
  char gender;
  int age;

public:
  Member() : name(nullptr), gender('-'), age(0) {}
  virtual ~Member() { delete[] name; }

  Member(char *name, char gender, int age) : gender(gender), age(age) {
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
  }

  Member(const Member &obj) : gender(obj.gender), age(obj.age) {
    this->name = new char[strlen(obj.name) + 1];
    strcpy(this->name, obj.name);
  }

  Member &operator=(const Member &obj) {
    if (this == &obj)
      return *this;
    this->gender = obj.gender;
    this->age = obj.age;

    delete[] this->name;
    this->name = new char[strlen(obj.name) + 1];
    strcpy(this->name, obj.name);

    return *this;
  }

  //------------------------
  virtual void input(char *name, char gender, int age) {
    if (name) {
      delete[] this->name;
      this->name = new char[strlen(name) + 1];
      strcpy(this->name, name);
    }

    this->gender = gender;
    this->age = age;
  }

  virtual void display() const {
    cout << "Name: " << name << endl;
    cout << "Gender: " << gender << endl;
    cout << "Age: " << age << endl;
  }

  virtual void update(char *name, char gender, int age) {
    this->age = age;
    this->gender = gender;
    delete[] this->name;
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
  }

  virtual const char *getType() const { return "Person"; }
};

class Employee : public Member {
  int empID;
  double salary;

public:
  Employee() : Member(), empID(0), salary(0) {}

  Employee(char *name, char gender, int age, int empID, double salary)
      : Member(name, gender, age), empID(empID), salary(salary) {}

  Employee(const Employee &obj)
      : Member(obj), empID(obj.empID), salary(obj.salary) {}

  Employee &operator=(const Employee &obj) {
    Member::operator=(obj);
    empID = obj.empID;
    salary = obj.salary;
  }

  void input(char *name, char gender, int age, int empID, double salary) {
    Member::input(name, gender, age);
    this->empID = empID;
    this->salary = salary;
  }

  void display() const {}
};
