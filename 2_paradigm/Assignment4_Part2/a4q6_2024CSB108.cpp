#include <iostream>
#include <string>
using namespace std;

class Cricketer {
protected:
  string name;
  string country;

public:
  Cricketer(string n, string c) {
    name = n;
    country = c;
  }
};

class Batsman : virtual public Cricketer {
protected:
  int *runs;

public:
  Batsman(string n, string c) : Cricketer(n, c) { runs = nullptr; }
};

class Bowler : virtual public Cricketer {
protected:
  int *wickets;

public:
  Bowler(string n, string c) : Cricketer(n, c) { wickets = nullptr; }
};

class AllRounder : public Batsman, public Bowler {
private:
  string *opponent;
  int matches;
  int capacity;

public:
  AllRounder(string n, string c)
      : Cricketer(n, c), Batsman(n, c), Bowler(n, c) {
    matches = 0;
    capacity = 2;

    runs = new int[capacity];
    wickets = new int[capacity];
    opponent = new string[capacity];
  }

  void resize() {
    capacity *= 2;

    int *newRuns = new int[capacity];
    int *newWickets = new int[capacity];
    string *newOpponent = new string[capacity];

    for (int i = 0; i < matches; i++) {
      newRuns[i] = runs[i];
      newWickets[i] = wickets[i];
      newOpponent[i] = opponent[i];
    }

    delete[] runs;
    delete[] wickets;
    delete[] opponent;

    runs = newRuns;
    wickets = newWickets;
    opponent = newOpponent;
  }

  void insertRecords() {
    int newMatches;
    cout << "Enter number of matches to add: ";
    cin >> newMatches;

    for (int i = 0; i < newMatches; i++) {
      if (matches == capacity) {
        resize();
      }

      cout << "\nMatch " << matches + 1 << endl;

      cout << "Opponent country: ";
      cin >> opponent[matches];

      cout << "Runs scored: ";
      cin >> runs[matches];

      cout << "Wickets taken: ";
      cin >> wickets[matches];

      matches++;
    }
  }

  void battingAverage() {
    if (matches == 0) {
      cout << "No data available.\n";
      return;
    }

    int total = 0;
    for (int i = 0; i < matches; i++)
      total += runs[i];

    cout << "Batting Average = " << (float)total / matches << endl;
  }

  void totalWickets() {
    if (matches == 0) {
      cout << "No data available.\n";
      return;
    }

    int total = 0;
    for (int i = 0; i < matches; i++)
      total += wickets[i];

    cout << "Total Wickets = " << total << endl;
  }

  void highestRuns() {
    if (matches == 0) {
      cout << "No data available.\n";
      return;
    }

    int maxR = runs[0];
    string team = opponent[0];

    for (int i = 1; i < matches; i++) {
      if (runs[i] > maxR) {
        maxR = runs[i];
        team = opponent[i];
      }
    }

    cout << "Highest Runs: " << maxR << " against " << team << endl;
  }

  void highestWickets() {
    if (matches == 0) {
      cout << "No data available.\n";
      return;
    }

    int maxW = wickets[0];
    string team = opponent[0];

    for (int i = 1; i < matches; i++) {
      if (wickets[i] > maxW) {
        maxW = wickets[i];
        team = opponent[i];
      }
    }

    cout << "Highest Wickets: " << maxW << " against " << team << endl;
  }

  void displayPlayer() {
    cout << "\nName: " << name;
    cout << "\nCountry: " << country << endl;
  }

  ~AllRounder() {
    delete[] runs;
    delete[] wickets;
    delete[] opponent;
  }
};

int main() {
  string name, country;
  int choice;
  cout << "Enter player name: ";
  getline(cin, name);

  cout << "Enter country: ";
  getline(cin, country);

  AllRounder player(name, country);

  do {
    cout << "\n\tChoose an option:\n";
    cout << "1. Insert Records\n";
    cout << "2. Display Player\n";
    cout << "3. Batting Average\n";
    cout << "4. Total Wickets\n";
    cout << "5. Highest Runs\n";
    cout << "6. Highest Wickets\n";
    cout << "0. Exit\n";
    cout << "Choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
      player.insertRecords();
      break;
    case 2:
      player.displayPlayer();
      break;
    case 3:
      player.battingAverage();
      break;
    case 4:
      player.totalWickets();
      break;
    case 5:
      player.highestRuns();
      break;
    case 6:
      player.highestWickets();
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
