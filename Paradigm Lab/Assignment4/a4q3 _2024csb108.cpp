#include <iostream>

using std::cin, std::cout, std::endl;

class Container {
  static int shape_count;

public:
  Container() { shape_count++; }
  virtual double volume() = 0;
  static int getShapeCount() { return shape_count; }
  virtual ~Container() { shape_count--; }
};

int Container::shape_count = 0;

class Box : public Container {
  double length, breadth, height;

  static int Box_count;

public:
  Box() : length(0), breadth(0), height(0) { Box_count++; }
  Box(double l, double b, double h) : length(l), breadth(b), height(h) {
    Box_count++;
  }
  ~Box() { Box_count--; }

  double volume() { return length * breadth * height; }

  static int getBoxCount() { return Box_count; }

  void update(double l = 0, double b = 0, double h = 0) {
    length = l;
    breadth = b;
    height = h;
  }
};

int Box::Box_count = 0;

class Cylinder : public Container {
  double radius, height;

  static int Cylinder_count;

public:
  Cylinder() : radius(0), height(0) { Cylinder_count++; }
  Cylinder(double r, double h) : radius(r), height(h) { Cylinder_count++; }
  ~Cylinder() { Cylinder_count--; }

  double volume() { return 3.1415 * radius * radius * height; }
  static int getCylinderCount() { return Cylinder_count; }

  void update(double radius, double height) {
    this->radius = radius;
    this->height = height;
  }
};

int Cylinder::Cylinder_count = 0;

class Pyramid : public Container {
  double base, height;
  static int Pyramid_count;

public:
  Pyramid() : base(0), height(0) { Pyramid_count++; }
  Pyramid(double b, double h) : base(b), height(h) { Pyramid_count++; }
  ~Pyramid() { Pyramid_count--; }

  double volume() { return (1.0 / 3.0) * base * height; }
  static int getPyramidCount() { return Pyramid_count; }

  void update(double base, double height) {
    this->base = base;
    this->height = height;
  }
};

int Pyramid::Pyramid_count = 0;

int main() {
  Container **arr = nullptr;
  int size = 0;
  int choice;

  do {
    cout << "\n\tChoose an option:\n";
    cout << "1. Add Box\n";
    cout << "2. Add Cylinder\n";
    cout << "3. Add Pyramid\n";
    cout << "4. Total Volume\n";
    cout << "5. Show Counts\n";
    cout << "6. Exit\n";
    cout << "Enter choice: ";
    cin >> choice;

    if (choice >= 1 && choice <= 3) {
      Container **temp = new Container *[size + 1];
      for (int i = 0; i < size; i++) {
        temp[i] = arr[i];
      }
      delete[] arr;
      arr = temp;

      if (choice == 1) {
        double l, b, h;
        cout << "Enter length, breadth, height: ";
        cin >> l >> b >> h;
        arr[size] = new Box(l, b, h);
      } else if (choice == 2) {
        double r, h;
        cout << "Enter radius and height: ";
        cin >> r >> h;
        arr[size] = new Cylinder(r, h);
      } else if (choice == 3) {
        double base, h;
        cout << "Enter base area and height: ";
        cin >> base >> h;
        arr[size] = new Pyramid(base, h);
      }

      size++;
      cout << "Container added successfully.\n";
    }

    else if (choice == 4) {
      double total = 0;
      for (int i = 0; i < size; i++) {
        total += arr[i]->volume();
      }
      cout << "Total Volume = " << total << endl;
    }

    else if (choice == 5) {
      cout << "\n\tObject Counts:\n";
      cout << "Total Containers: " << Container::getShapeCount() << endl;
      cout << "Boxes: " << Box::getBoxCount() << endl;
      cout << "Cylinders: " << Cylinder::getCylinderCount() << endl;
      cout << "Pyramids: " << Pyramid::getPyramidCount() << endl;
    }

    else if (choice == 6) {
      cout << "Exiting...\n";
    }

    else {
      cout << "Invalid choice.\n";
    }

  } while (choice != 6);

  for (int i = 0; i < size; i++) {
    delete arr[i];
  }
  delete[] arr;

  return 0;
}
