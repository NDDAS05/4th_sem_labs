#include <cstring>
#include <iostream>
using std::cin, std::cout, std::endl;

/*
      ----Member----
      |           \
    Employee   Trainee
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
    if (this == &obj)
      return *this;

    Member::operator=(obj);
    empID = obj.empID;
    salary = obj.salary;
    return *this;
  }

  void input(char *name, char gender, int age, int empID, double salary) {
    Member::input(name, gender, age);
    this->empID = empID;
    this->salary = salary;
  }

  void display() const {
    cout << "Employee ID: " << empID << endl;
    Member::display();
    cout << "Salary: Rs." << salary << endl;
  }

  void update(char *name, char gender, int age, int empID, double salary) {
    Member::update(name, gender, age);
    this->empID = empID;
    this->salary = salary;
  }
};

class Trainee : public Member {
  char *department;
  char *skillset;
  int duration;
  double stipend;

public:
  Trainee()
      : Member(), department(nullptr), skillset(nullptr), duration(0),
        stipend(0) {}

  Trainee(char *name, char gender, int age, char *department, char *skillset,
          double stipend, double duration)
      : Member(name, gender, age), stipend(stipend), duration(duration) {

    if (department) {
      this->department = new char[strlen(department) + 1];
      strcpy(this->department, department);
    } else
      this->department = nullptr;

    if (skillset) {
      this->skillset = new char[strlen(skillset) + 1];
      strcpy(this->skillset, skillset);
    } else
      this->skillset = nullptr;
  }

  Trainee(const Trainee &obj)
      : Member(obj), stipend(obj.stipend), duration(obj.duration) {

    delete[] department;
    delete[] skillset;

    if (obj.department) {
      this->department = new char[strlen(obj.department) + 1];
      strcpy(this->department, obj.department);
    } else
      this->department = nullptr;

    if (obj.skillset) {
      this->skillset = new char[strlen(obj.skillset) + 1];
      strcpy(this->skillset, obj.skillset);
    } else
      this->skillset = nullptr;
  }

  Trainee &operator=(const Trainee &obj) {
    if (this == &obj)
      return *this;

    Member::operator=(obj);

    stipend = obj.stipend;
    duration = obj.duration;

    delete[] department;
    delete[] skillset;

    if (obj.department) {
      this->department = new char[strlen(obj.department) + 1];
      strcpy(this->department, obj.department);
    } else
      this->department = nullptr;

    if (obj.skillset) {
      this->skillset = new char[strlen(obj.skillset) + 1];
      strcpy(this->skillset, obj.skillset);
    } else
      this->skillset = nullptr;

    return *this;
  }

  void input(char *name, char gender, int age, char *department, char *skillset,
             double stipend, double duration) {
    Member::input(name, gender, age);
    this->stipend = stipend;
    this->duration = duration;

    delete[] department;
    delete[] skillset;

    if (department) {
      this->department = new char[strlen(department) + 1];
      strcpy(this->department, department);
    } else
      this->department = nullptr;

    if (skillset) {
      this->skillset = new char[strlen(skillset) + 1];
      strcpy(this->skillset, skillset);
    } else
      this->skillset = nullptr;
  }

  void display() const {
    Member::display();
    cout << "Department: " << department << endl;
    cout << "Skillset: " << skillset << endl;
    cout << "Duration: " << duration << endl;
    cout << "Stipend: Rs. " << stipend << endl;
  }

  void update(char *name, char gender, int age, char *department,
              char *skillset, double stipend, double duration) {

    Member::update(name, gender, age);
    this->stipend = stipend;
    this->duration = duration;

    delete[] department;
    delete[] skillset;

    if (department) {
      this->department = new char[strlen(department) + 1];
      strcpy(this->department, department);
    } else
      this->department = nullptr;

    if (skillset) {
      this->skillset = new char[strlen(skillset) + 1];
      strcpy(this->skillset, skillset);
    } else
      this->skillset = nullptr;
  }
};
