#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class ComplexNumber {
  double real;
  double img;

public:
  ComplexNumber() : real(0), img(0) {}
  ComplexNumber(double num) : real(num), img(0) {}
  ComplexNumber(double r, double i) : real(r), img(i) {}

  void show() const { cout << "( " << real << " ) + i( " << img << " )"; }

  friend const ComplexNumber operator+(const ComplexNumber &,
                                       const ComplexNumber &);
  friend const ComplexNumber operator-(const ComplexNumber &,
                                       const ComplexNumber &);
};

const ComplexNumber operator+(const ComplexNumber &obj1,
                              const ComplexNumber &obj2) {
  return ComplexNumber(obj1.real + obj2.real, obj1.img + obj2.img);
}

const ComplexNumber operator-(const ComplexNumber &obj1,
                              const ComplexNumber &obj2) {
  return ComplexNumber(obj1.real - obj2.real, obj1.img - obj2.img);
}

int main() {
  int choice;
  double r1, i1, r2, i2;

  while (true) {
    cout << "Assignment 3.2: Q4       " << endl;
    cout << "Choose option" << endl;
    cout << "================================" << endl;
    cout << "1. Perform Addition" << endl;
    cout << "2. Perform Subtraction" << endl;
    cout << "3. Exit" << endl;
    cout << "--------------------------------" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 3) {
      cout << "Exiting program..." << endl;
      break;
    }

    if (choice != 1 && choice != 2) {
      cout << "Invalid choice. Enter 1, 2, or 3." << endl;
      continue;
    }

    cout << "\nEnter first complex number" << endl;
    cout << "Enter real part: ";
    cin >> r1;
    cout << "Enter imaginary part: ";
    cin >> i1;
    ComplexNumber c1(r1, i1);

    cout << "\nEnter second complex number" << endl;
    cout << "Enter real part: ";
    cin >> r2;
    cout << "Enter imaginary part: ";
    cin >> i2;
    ComplexNumber c2(r2, i2);

    cout << "\nResult:" << endl;

    switch (choice) {
    case 1: {
      ComplexNumber result = c1 + c2;
      c1.show();
      cout << " + ";
      c2.show();
      cout << " = ";
      result.show();
      cout << endl;
      break;
    }
    case 2: {
      ComplexNumber result = c1 - c2;
      c1.show();
      cout << " - ";
      c2.show();
      cout << " = ";
      result.show();
      cout << endl;
      break;
    }
    }
  }

  return 0;
}
