#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using std::cin, std::cout, std::endl, std::string;

class Vehicle {
protected:
  string id, brand;
  int year;
  bool is_running;

public:
  Vehicle() : id(""), brand(""), year(0), is_running(false) {}

  Vehicle(string id, string brand, int year)
      : id(id), brand(brand), year(year), is_running(false) {}

  virtual ~Vehicle() {}

  virtual void start() {
    is_running = true;
    cout << "Vehicle [ " << getType() << " ] started.\n";
  }

  virtual void stop() {
    is_running = false;
    cout << "Vehicle [ " << getType() << " ] stopped.\n";
  }

  virtual string getType() const = 0;
  virtual void displayInfo() const = 0;
  virtual void saveInfo(std::ofstream &out) const = 0;

  string getID() const { return id; }
  string getBrand() const { return brand; }
  int getYear() const { return year; }
  bool isRunning() const { return is_running; }
};

class Car : public Vehicle {
  int num_of_doors;
  string fuel_type;

public:
  Car() : Vehicle(), num_of_doors(0), fuel_type("") {}

  Car(string id, string brand, int year, int num_of_doors, string fuel_type)
      : Vehicle(id, brand, year), num_of_doors(num_of_doors),
        fuel_type(fuel_type) {}

  string getType() const { return "Car"; }

  void displayInfo() const {
    cout << "  [Car] " << endl
         << "ID=" << id << endl
         << "  Brand=" << brand << endl
         << "  Year=" << year << endl
         << "  Doors=" << num_of_doors << endl
         << "  Fuel=" << fuel_type << endl
         << "  Status=" << (is_running ? "Running" : "Stopped") << "\n";
  }

  void saveInfo(std::ofstream &out) const {
    out << "Car|" << id << "|" << brand << "|" << year << "|" << num_of_doors
        << "|" << fuel_type << "\n";
  }
};

class Truck : public Vehicle {
  double payloadTons;
  bool hasRefrigeration;

public:
  Truck() : Vehicle(), payloadTons(0.0), hasRefrigeration(false) {}
  Truck(string id, string brand, int year, double payloadTons,
        bool hasRefrigeration)
      : Vehicle(id, brand, year), payloadTons(payloadTons),
        hasRefrigeration(hasRefrigeration) {}

  string getType() const { return "Truck"; }

  void displayInfo() const {
    cout << "  [Truck]" << endl
         << "ID=" << id << endl
         << "  Brand=" << brand << endl
         << "  Year=" << year << endl
         << "  Payload=" << payloadTons << "t" << endl
         << "  Refrigerated=" << (hasRefrigeration ? "Yes" : "No") << endl
         << "  Status=" << (is_running ? "Running" : "Stopped") << "\n";
  }

  void saveInfo(std::ofstream &out) const {
    out << "Truck|" << id << "|" << brand << "|" << year << "|" << payloadTons
        << "|" << hasRefrigeration << "\n";
  }
};

class Bus : public Vehicle {
  int capacity;
  string routeNumber;

public:
  Bus(string id, string brand, int year, int capacity, string routeNumber)
      : Vehicle(id, brand, year), capacity(capacity), routeNumber(routeNumber) {
  }

  string getType() const { return "Bus"; }

  void displayInfo() const {
    cout << "  [Bus]" << endl
         << "  ID=" << id << endl
         << "  Brand=" << brand << endl
         << "  Year=" << year << endl
         << "  Capacity=" << capacity << endl
         << "  Route=" << routeNumber << endl
         << "  Status=" << (is_running ? "Running" : "Stopped") << "\n";
  }

  void saveInfo(std::ofstream &out) const {
    out << "Bus|" << id << "|" << brand << "|" << year << "|" << capacity << "|"
        << routeNumber << "\n";
  }
};

class FleetManager {

  Vehicle **fleet;
  int capacity;
  int count;

  void resize() {
    capacity = (capacity == 0) ? 2 : capacity * 2;
    Vehicle **newFleet = new Vehicle *[capacity];

    for (int i = 0; i < count; ++i) {
      newFleet[i] = fleet[i];
    }

    delete[] fleet;
    fleet = newFleet;
  }

public:
  FleetManager(int initialCap = 2) {
    capacity = initialCap;
    count = 0;
    fleet = new Vehicle *[capacity];
  }

  ~FleetManager() {
    clearFleetObj();
    delete[] fleet;
  }

  void clearFleetObj() {
    for (int i = 0; i < count; ++i) {
      delete fleet[i];
    }
    count = 0;
  }

  void addVehicle(Vehicle *v) {
    if (count == capacity) {
      resize();
    }
    fleet[count] = v;
    count++;
  }

  void displayAll() const {
    for (int i = 0; i < count; ++i) {
      fleet[i]->displayInfo();
    }
  }

  void startAll() const {
    for (int i = 0; i < count; ++i) {
      fleet[i]->start();
    }
  }

  void saveFleet(const string &filename) const {
    std::ofstream outFile(filename);
    if (!outFile) {
      cout << "Error writing to file." << endl;
      return;
    }
    for (int i = 0; i < count; ++i) {
      fleet[i]->saveInfo(outFile);
    }
    outFile.close();
  }

  void loadFleet(const string &filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
      cout << "Error reading from file" << endl;
      return;
    }

    clearFleetObj();

    string line;

    while (getline(inFile, line)) {
      if (line.empty())
        continue;

      std::stringstream ss(line);
      string type;

      getline(ss, type, '|');

      if (type == "Car") {
        string id, brand, yearStr, doorsStr, fuel;
        getline(ss, id, '|');
        getline(ss, brand, '|');
        getline(ss, yearStr, '|');
        getline(ss, doorsStr, '|');
        getline(ss, fuel, '|');

        int year = stoi(yearStr);
        int doors = stoi(doorsStr);

        addVehicle(new Car(id, brand, year, doors, fuel));
      }

      else if (type == "Truck") {
        string id, brand, yearStr, payloadStr, refrigStr;
        getline(ss, id, '|');
        getline(ss, brand, '|');
        getline(ss, yearStr, '|');
        getline(ss, payloadStr, '|');
        getline(ss, refrigStr, '|');

        int year = stoi(yearStr);
        double payload = stod(payloadStr);
        bool hasRefrigeration = stoi(refrigStr); // 0 or 1

        addVehicle(new Truck(id, brand, year, payload, hasRefrigeration));
      }

      else if (type == "Bus") {
        string id, brand, yearStr, capStr, route;
        getline(ss, id, '|');
        getline(ss, brand, '|');
        getline(ss, yearStr, '|');
        getline(ss, capStr, '|');
        getline(ss, route, '|');

        int year = stoi(yearStr);
        int capacity = stoi(capStr);

        addVehicle(new Bus(id, brand, year, capacity, route));
      }
    }

    inFile.close();
  }
};

int main() {
  FleetManager fm;
  int choice;

  do {
    cout << "\n\tChoose an option:\n";
    cout << "1. Add Vehicle\n";
    cout << "2. Display All Vehicles\n";
    cout << "3. Start All Vehicles\n";
    cout << "4. Save Fleet to File\n";
    cout << "5. Load Fleet from File\n";
    cout << "0. Exit\n";
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice) {

    case 1: {
      int type;
      cout << "\nSelect Vehicle Type:\n";
      cout << "1. Car\n2. Truck\n3. Bus\n";
      cout << "Enter choice: ";
      cin >> type;

      string id, brand;
      int year;

      cout << "Enter ID: ";
      cin >> id;
      cout << "Enter Brand: ";
      cin >> brand;
      cout << "Enter Year: ";
      cin >> year;

      if (type == 1) {
        int doors;
        string fuel;

        cout << "Enter number of doors: ";
        cin >> doors;
        cout << "Enter fuel type: ";
        cin >> fuel;

        fm.addVehicle(new Car(id, brand, year, doors, fuel));
      }

      else if (type == 2) {
        double payload;
        int refrig;

        cout << "Enter payload (tons): ";
        cin >> payload;
        cout << "Refrigeration? (1 = Yes, 0 = No): ";
        cin >> refrig;

        fm.addVehicle(new Truck(id, brand, year, payload, refrig));
      }

      else if (type == 3) {
        int capacity;
        string route;

        cout << "Enter capacity: ";
        cin >> capacity;
        cout << "Enter route number: ";
        cin >> route;

        fm.addVehicle(new Bus(id, brand, year, capacity, route));
      }

      else {
        cout << "Invalid vehicle type.\n";
      }

      break;
    }

    case 2:
      fm.displayAll();
      break;

    case 3:
      fm.startAll();
      break;

    case 4: {
      string filename;
      cout << "Enter filename: ";
      cin >> filename;
      fm.saveFleet(filename);
      cout << "Fleet saved.\n";
      break;
    }

    case 5: {
      string filename;
      cout << "Enter filename: ";
      cin >> filename;
      fm.loadFleet(filename);
      cout << "Fleet loaded.\n";
      break;
    }

    case 0:
      cout << "Exiting...\n";
      break;

    default:
      cout << "Invalid choice.\n";
    }

  } while (choice != 0);

  return 0;
}
