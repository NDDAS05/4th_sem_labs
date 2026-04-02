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

  Member(const char *name, char gender, int age) : gender(gender), age(age) {
    if (name) {
      this->name = new char[strlen(name) + 1];
      strcpy(this->name, name);
    } else
      this->name = nullptr;
  }

  Member(const Member &obj) : gender(obj.gender), age(obj.age) {
    if (obj.name) {
      this->name = new char[strlen(obj.name) + 1];
      strcpy(this->name, obj.name);
    } else
      name = nullptr;
  }

  Member &operator=(const Member &obj) {
    if (this == &obj)
      return *this;
    this->gender = obj.gender;
    this->age = obj.age;

    if (obj.name) {
      name = new char[strlen(obj.name) + 1];
      strcpy(name, obj.name);
    } else
      name = nullptr;

    return *this;
  }

  virtual void input(const char *name, char gender, int age) {

    delete[] this->name;
    if (name) {
      this->name = new char[strlen(name) + 1];
      strcpy(this->name, name);
    } else
      this->name = nullptr;

    this->gender = gender;
    this->age = age;
  }

  virtual void display() const {
    cout << "Name: " << (name ? name : "N/A") << endl;
    cout << "Gender: " << gender << endl;
    cout << "Age: " << age << endl;
  }

  virtual const char *getType() const { return "Member"; }
};

class Employee : public Member {
  int empID;
  double salary;

public:
  Employee() : Member(), empID(0), salary(0) {}

  Employee(const char *name, char gender, int age, int empID, double salary)
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

  virtual ~Employee() {}

  virtual void input(const char *name, char gender, int age, int empID,
                     double salary) {
    Member::input(name, gender, age);
    this->empID = empID;
    this->salary = salary;
  }

  void display() const {
    cout << "Employee ID: " << empID << endl;
    Member::display();
    cout << "Salary: Rs." << salary << endl;
  }

  int getEmpID() const { return empID; }

  const char *getType() const { return "Employee"; }
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

  Trainee(const char *name, char gender, int age, const char *department,
          const char *skillset, double stipend, double duration)
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

    delete[] this->department;
    delete[] this->skillset;

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

  ~Trainee() {
    delete[] department;
    delete[] skillset;
  }

  void input(const char *name, char gender, int age, const char *department,
             const char *skillset, double stipend, double duration) {
    Member::input(name, gender, age);
    this->stipend = stipend;
    this->duration = duration;

    delete[] this->department;
    delete[] this->skillset;

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

  const char *getType() const { return "Trainee"; }
};

class Developer : public Employee {
  char *department;
  char *skillset;
  char *project;
  int experience;

public:
  Developer()
      : Employee(), department(nullptr), skillset(nullptr), project(nullptr),
        experience(0) {}

  Developer(const char *name, char gender, int age, int empID, double salary,
            const char *department, const char *skillset, const char *project,
            int experience)
      : Employee(name, gender, age, empID, salary), experience(experience) {
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

    if (project) {
      this->project = new char[strlen(project) + 1];
      strcpy(this->project, project);
    } else
      this->project = nullptr;
  }

  Developer(const Developer &obj) : Employee(obj), experience(obj.experience) {

    if (obj.department) {
      department = new char[strlen(obj.department) + 1];
      strcpy(department, obj.department);
    } else
      department = nullptr;

    if (obj.project) {
      project = new char[strlen(obj.project) + 1];
      strcpy(project, obj.project);
    } else
      project = nullptr;

    if (obj.skillset) {
      skillset = new char[strlen(obj.skillset) + 1];
      strcpy(skillset, obj.skillset);
    } else
      skillset = nullptr;
  }

  Developer &operator=(const Developer &obj) {
    if (this == &obj)
      return *this;

    Employee::operator=(obj);
    experience = obj.experience;

    delete[] department;
    delete[] skillset;
    delete[] project;

    if (obj.department) {
      department = new char[strlen(obj.department) + 1];
      strcpy(department, obj.department);
    } else
      department = nullptr;

    if (obj.project) {
      project = new char[strlen(obj.project) + 1];
      strcpy(project, obj.project);
    } else
      project = nullptr;

    if (obj.skillset) {
      skillset = new char[strlen(obj.skillset) + 1];
      strcpy(skillset, obj.skillset);
    } else
      skillset = nullptr;

    return *this;
  }

  ~Developer() {
    delete[] department;
    delete[] skillset;
    delete[] project;
  }

  void input(const char *name, char gender, int age, int empID, double salary,
             const char *department, const char *skillset, const char *project,
             int experience) {

    Employee::input(name, gender, age, empID, salary);
    this->experience = experience;

    delete[] this->department;
    delete[] this->skillset;
    delete[] this->project;

    this->department = department ? new char[strlen(department) + 1] : nullptr;
    if (department)
      strcpy(this->department, department);

    this->skillset = skillset ? new char[strlen(skillset) + 1] : nullptr;
    if (skillset)
      strcpy(this->skillset, skillset);

    this->project = project ? new char[strlen(project) + 1] : nullptr;
    if (project)
      strcpy(this->project, project);
  }

  void display() const {
    Employee::display();
    cout << "Department: " << (department ? department : "N/A") << endl;
    cout << "Skillset: " << (skillset ? skillset : "N/A") << endl;
    cout << "Project: " << (project ? project : "N/A") << endl;
    cout << "Experience: " << experience << endl;
  }

  const char *getType() const { return "Developer"; }
};

class SystemAdmin : public Employee {
  int workload;

public:
  SystemAdmin() : Employee(), workload(0) {}

  SystemAdmin(const char *name, char gender, int age, int empID, double salary,
              int workload)
      : Employee(name, gender, age, empID, salary), workload(workload) {}

  SystemAdmin(const SystemAdmin &obj) : Employee(obj), workload(obj.workload) {}

  SystemAdmin &operator=(const SystemAdmin &obj) {
    if (this == &obj)
      return *this;

    Employee::operator=(obj);
    workload = obj.workload;
    return *this;
  }

  ~SystemAdmin() {}

  void input(const char *name, char gender, int age, int empID, double salary,
             int workload) {
    Employee::input(name, gender, age, empID, salary);
    this->workload = workload;
  }

  void display() const {
    Employee::display();
    cout << "Workload: " << workload << endl;
  }

  const char *getType() const { return "SystemAdmin"; }
};
