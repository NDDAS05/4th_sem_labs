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

    delete[] name;

    gender = obj.gender;
    age = obj.age;

    if (obj.name) {
      name = new char[strlen(obj.name) + 1];
      strcpy(name, obj.name);
    } else
      name = nullptr;

    return *this;
  }

  virtual void input() = 0;
  virtual void update() = 0;

  virtual void display() const {
    cout << "Name: " << (name ? name : "N/A") << endl;
    cout << "Gender: " << gender << endl;
    cout << "Age: " << age << endl;
  }

  virtual const char *getType() const = 0;

protected:
  void setBasic(const char *n, char g, int a) {
    delete[] name;
    if (n) {
      name = new char[strlen(n) + 1];
      strcpy(name, n);
    } else
      name = nullptr;

    gender = g;
    age = a;
  }

  const char* getNam() const { return name; }
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

protected:
  void setEmp(int id, double sal) {
    empID = id;
    salary = sal;
  }

public:
  void display() const {
    cout << "Employee ID: " << empID << endl;
    Member::display();
    cout << "Salary: Rs." << salary << endl;
  }

  int getEmpID() const { return empID; }
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

  Trainee(const Trainee &obj)
      : Member(obj), duration(obj.duration), stipend(obj.stipend) {

    department = skillset = nullptr;

    if (obj.department) {
      department = new char[strlen(obj.department) + 1];
      strcpy(department, obj.department);
    }

    if (obj.skillset) {
      skillset = new char[strlen(obj.skillset) + 1];
      strcpy(skillset, obj.skillset);
    }
  }

  Trainee &operator=(const Trainee &obj) {
    if (this == &obj)
      return *this;

    Member::operator=(obj);

    duration = obj.duration;
    stipend = obj.stipend;

    delete[] department;
    delete[] skillset;

    if (obj.department) {
      department = new char[strlen(obj.department) + 1];
      strcpy(department, obj.department);
    } else
      department = nullptr;

    if (obj.skillset) {
      skillset = new char[strlen(obj.skillset) + 1];
      strcpy(skillset, obj.skillset);
    } else
      skillset = nullptr;

    return *this;
  }

  ~Trainee() {
    delete[] department;
    delete[] skillset;
  }

  void input() {
    char name[100], gender;
    int age, dur;
    double stip;
    char dept[100], skill[100];

    cin.ignore();
    cout << "Name: ";
    cin.getline(name, 100);

    cout << "Gender: ";
    cin >> gender;

    cout << "Age: ";
    cin >> age;

    cin.ignore();
    cout << "Department: ";
    cin.getline(dept, 100);

    cout << "Skillset: ";
    cin.getline(skill, 100);

    cout << "Duration: ";
    cin >> dur;

    cout << "Stipend: ";
    cin >> stip;

    setBasic(name, gender, age);

    delete[] department;
    delete[] skillset;

    department = new char[strlen(dept) + 1];
    strcpy(department, dept);

    skillset = new char[strlen(skill) + 1];
    strcpy(skillset, skill);

    duration = dur;
    stipend = stip;
  }

  void update() { input(); }

  void display() const {
    Member::display();
    cout << "Department: " << (department ? department : "N/A") << endl;
    cout << "Skillset: " << (skillset ? skillset : "N/A") << endl;
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

  Developer(const Developer &obj) : Employee(obj), experience(obj.experience) {

    department = skillset = project = nullptr;

    if (obj.department) {
      department = new char[strlen(obj.department) + 1];
      strcpy(department, obj.department);
    }

    if (obj.skillset) {
      skillset = new char[strlen(obj.skillset) + 1];
      strcpy(skillset, obj.skillset);
    }

    if (obj.project) {
      project = new char[strlen(obj.project) + 1];
      strcpy(project, obj.project);
    }
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

    if (obj.skillset) {
      skillset = new char[strlen(obj.skillset) + 1];
      strcpy(skillset, obj.skillset);
    } else
      skillset = nullptr;

    if (obj.project) {
      project = new char[strlen(obj.project) + 1];
      strcpy(project, obj.project);
    } else
      project = nullptr;

    return *this;
  }

  ~Developer() {
    delete[] department;
    delete[] skillset;
    delete[] project;
  }

  void input() {
    char name[100], gender;
    int age, empID, exp;
    double salary;
    char dept[100], skill[100], proj[100];

    cin.ignore();
    cout << "Name: ";
    cin.getline(name, 100);

    cout << "Gender: ";
    cin >> gender;

    cout << "Age: ";
    cin >> age;

    cout << "EmpID: ";
    cin >> empID;

    cout << "Salary: ";
    cin >> salary;

    cin.ignore();
    cout << "Department: ";
    cin.getline(dept, 100);

    cout << "Skillset: ";
    cin.getline(skill, 100);

    cout << "Project: ";
    cin.getline(proj, 100);

    cout << "Experience: ";
    cin >> exp;

    setBasic(name, gender, age);
    setEmp(empID, salary);

    delete[] department;
    delete[] skillset;
    delete[] project;

    department = new char[strlen(dept) + 1];
    strcpy(department, dept);

    skillset = new char[strlen(skill) + 1];
    strcpy(skillset, skill);

    project = new char[strlen(proj) + 1];
    strcpy(project, proj);

    experience = exp;
  }

  void update() { input(); }

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

  SystemAdmin(const SystemAdmin &obj)
      : Employee(obj), workload(obj.workload) {}

  SystemAdmin &operator=(const SystemAdmin &obj) {
    if (this == &obj)
      return *this;

    Employee::operator=(obj);
    workload = obj.workload;
    return *this;
  }

  void input() {
    char name[100], gender;
    int age, empID, wl;
    double salary;

    cin.ignore();
    cout << "Name: ";
    cin.getline(name, 100);

    cout << "Gender: ";
    cin >> gender;

    cout << "Age: ";
    cin >> age;

    cout << "EmpID: ";
    cin >> empID;

    cout << "Salary: ";
    cin >> salary;

    cout << "Workload: ";
    cin >> wl;

    setBasic(name, gender, age);
    setEmp(empID, salary);
    workload = wl;
  }

  void update() { input(); }

  void display() const {
    Employee::display();
    cout << "Workload: " << workload << endl;
  }

  const char *getType() const { return "SystemAdmin"; }
};


int main() {
  Member *arr[100];
  int count = 0, choice;

  do {
    cout << "\nChoose an option:\n----------------------------\n";
    cout << "\n1. Add Dev  2. Add Admin  3. Add Trainee\n";
    cout << "4. Display  5. Update  6. Exit\nEnter choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
      arr[count] = new Developer();
      arr[count++]->input();
      cout<<"Developer added at index "<<count-1<<endl;
      break;

    case 2:
      arr[count] = new SystemAdmin();
      arr[count++]->input();
      cout<<"System admin added at index "<<count-1<<endl;
      break;

    case 3:
      arr[count] = new Trainee();
      arr[count++]->input();
      cout<<"Trainee added at index "<<count-1<<endl;
      break;

    case 4:
      for (int i = 0; i < count; i++) {
        cout << "\nType: " << arr[i]->getType() << endl;
        arr[i]->display();
      }
      break;

    case 5: {
      int idx;
      cout << "Index: ";
      cin >> idx;
      if (idx >= 0 && idx < count)
        arr[idx]->update();
      else
        cout << "Invalid index.\n";
      break;
    }

    case 6:
      break;

    default:
      cout << "Invalid option.\n";
    }

  } while (choice != 6);

  for (int i = 0; i < count; i++)
    delete arr[i];

  return 0;
}