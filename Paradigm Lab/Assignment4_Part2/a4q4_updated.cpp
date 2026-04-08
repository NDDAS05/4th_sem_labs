#include <fstream>
#include <iostream>
#include <memory>
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
    cout << "  [Car]   ID=" << id << endl
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
    cout << "  [Truck] ID=" << id << endl
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
    cout << "  [Bus]   ID=" << id << "  Brand=" << brand << "  Year=" << year
         << "  Capacity=" << capacity << "  Route=" << routeNumber
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
        if (line.empty()) continue;

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
