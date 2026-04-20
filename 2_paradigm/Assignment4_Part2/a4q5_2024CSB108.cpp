#include <iostream>
#include <string>
#define PI 3.1415
using namespace std;

class shape {
public:
  virtual void readInput() = 0;
  virtual double displayArea() = 0;
  virtual void objInfo() = 0;
  virtual string getType() const = 0;
  virtual ~shape() {}
};

class Triangle : public shape {
  double height, base;

public:
  Triangle() : height(0), base(0) {}

  void readInput() {
    cout << "Enter height: ";
    cin >> height;
    cout << "Enter base: ";
    cin >> base;
  }

  string getType() const { return "Triangle"; }

  double displayArea() { return 0.5 * base * height; }

  void objInfo() {
    cout << "\nShape: " << getType() << endl;
    cout << "Height: " << height << ", Base: " << base << endl;
    cout << "Area: " << displayArea() << endl;
  }
};

class Rectangle : public shape {
  double height, width;

public:
  Rectangle() : height(0), width(0) {}

  void readInput() {
    cout << "Enter height: ";
    cin >> height;
    cout << "Enter width: ";
    cin >> width;
  }

  string getType() const { return "Rectangle"; }

  double displayArea() { return height * width; }

  void objInfo() {
    cout << "\nShape: " << getType() << endl;
    cout << "Height: " << height << ", Width: " << width << endl;
    cout << "Area: " << displayArea() << endl;
  }
};

class Circle : public shape {
  double radius;

public:
  Circle() : radius(0) {}

  void readInput() {
    cout << "Enter radius: ";
    cin >> radius;
  }

  string getType() const { return "Circle"; }

  double displayArea() { return PI * radius * radius; }

  void objInfo() {
    cout << "\nShape: " << getType() << endl;
    cout << "Radius: " << radius << endl;
    cout << "Area: " << displayArea() << endl;
  }
};

class ShapeStack {
  shape **shapeStk;
  int topIndex;
  int currentSize;
  int maxCapacity;

  void inflate() {
    maxCapacity *= 2;
    shape **newStk = new shape *[maxCapacity];

    for (int i = 0; i < currentSize; i++) {
      newStk[i] = shapeStk[i];
    }

    delete[] shapeStk;
    shapeStk = newStk;
  }

public:
  ShapeStack(int cap) {
    maxCapacity = cap;
    currentSize = 0;
    topIndex = -1;
    shapeStk = new shape *[maxCapacity];
  }

  void push(shape *s) {
    if (currentSize == maxCapacity) {
      inflate();
    }
    shapeStk[++topIndex] = s;
    currentSize++;
  }

  void pop() {
    if (topIndex == -1) {
      cout << "Stack Underflow\n";
      return;
    }
    delete shapeStk[topIndex];
    topIndex--;
    currentSize--;
  }

  shape *top() {
    if (topIndex == -1) {
      cout << "Stack Empty\n";
      return nullptr;
    }
    return shapeStk[topIndex];
  }

  void Display() {
    if (topIndex == -1) {
      cout << "Stack is Empty\n";
      return;
    }

    cout << "\n===== STACK CONTENTS =====\n";
    for (int i = topIndex; i >= 0; i--) {
      shapeStk[i]->objInfo();
      cout << "----------------------";
    }
  }

  double TotalAreaCovered() {
    double total = 0;
    for (int i = 0; i < currentSize; i++) {
      total += shapeStk[i]->displayArea();
    }
    return total;
  }

  ~ShapeStack() {
    for (int i = 0; i < currentSize; i++) {
      delete shapeStk[i];
    }
    delete[] shapeStk;
  }
};

int main() {
  ShapeStack stk(2);
  int choice;

  do {
    cout << "\n\tChoose an option:\n";
    cout << "1. Push Shape\n";
    cout << "2. Pop Shape\n";
    cout << "3. View Top Shape\n";
    cout << "4. Display Stack\n";
    cout << "5. Total Area Covered\n";
    cout << "0. Exit\n";
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice) {
    case 1: {
      int type;
      cout << "\nSelect Shape:\n";
      cout << "1. Triangle\n2. Rectangle\n3. Circle\n";
      cin >> type;

      shape *s = nullptr;

      switch (type) {
      case 1:
        s = new Triangle();
        break;
      case 2:
        s = new Rectangle();
        break;
      case 3:
        s = new Circle();
        break;
      default:
        cout << "Invalid shape.\n";
        continue;
      }

      s->readInput();
      stk.push(s);
      cout << "Shape pushed.\n";
      break;
    }

    case 2:
      stk.pop();
      break;

    case 3: {
      shape *t = stk.top();
      if (t)
        t->objInfo();
      break;
    }

    case 4:
      stk.Display();
      break;

    case 5:
      cout << "Total Area Covered = " << stk.TotalAreaCovered() << endl;
      break;

    case 0:
      cout << "Exiting...\n";
      break;

    default:
      cout << "Invalid choice.\n";
    }

  } while (choice != 0);

  return 0;
}
