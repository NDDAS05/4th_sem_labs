#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;

template <typename T> inline T *init(int &size) {
  T *arr = new T[size];
  return arr;
}

template <typename T> inline void printer(const T *arr, int &size) {
  for (int i = 0; i < size; i++) {
    cout << arr[i] << " ";
  }
  cout << endl;
}

template <typename T> inline T *remove(T *arr) {
  if (arr != nullptr) {
    delete[] arr;
  }
  return nullptr;
}

typedef struct {
  std::string str;
  int val;
} structure;

template <typename T> void insertionSort(T *arr, int &size) {
  for (int i = 1; i < size; i++) {
    T curr = arr[i];
    int prev = i - 1;
    while (prev >= 0) {
      if (arr[prev] > curr) {
        arr[prev + 1] = arr[prev];
        prev--;
      } else
        break;
    }
    arr[prev + 1] = curr;
  }
}

int main() {
  int choice, value;
  bool flag = true;
  while (flag) {
    cout << "Choose an option: " << endl;
    cout << "1. Sort array of integers" << endl;
    cout << "2. Sort array of floats" << endl;
    cout << "3. Sort array of doubles" << endl;
    cout << "4. Sort array of short integers" << endl;
    cout << "5. Try to sort an array of structures" << endl;
    cout << "6. Exit";
    cout << "\nEnter option: ";
    cin >> choice;

    switch (choice) {
    case 1: {
      cout << "Enter number of integers: ";
      cin >> value;

      int *arr = init<int>(value);
      cout << "Enter data:\n";
      for (int i = 0; i < value; i++) {
        cin >> arr[i];
      }

      insertionSort(arr, value);
      printer(arr, value);
      remove(arr);
      break;
    }

    case 2: {
      cout << "Enter number of floats: ";
      cin >> value;

      float *arr = init<float>(value);
      cout << "Enter data:\n";
      for (int i = 0; i < value; i++) {
        cin >> arr[i];
      }

      insertionSort(arr, value);
      printer(arr, value);
      remove(arr);
      break;
    }
    case 3: {
      cout << "Enter number of doubles: ";
      cin >> value;

      double *arr = init<double>(value);
      cout << "Enter data:\n";
      for (int i = 0; i < value; i++) {
        cin >> arr[i];
      }

      insertionSort(arr, value);
      printer(arr, value);
      remove(arr);
      break;
    }
    case 4: {
      cout << "Enter number of short integers: ";
      cin >> value;

      short *arr = init<short>(value);
      cout << "Enter data:\n";
      for (int i = 0; i < value; i++) {
        cin >> arr[i];
      }

      insertionSort(arr, value);
      printer(arr, value);
      remove(arr);
      break;
    }
    case 5: {
      cout << "Enter number of structures: ";
      cin >> value;
      structure *arr = init<structure>(value);
      cout << "Enter data: ";
      for (int i = 0; i < value; i++) {
        cin.ignore();
        cout << "Data for string field: ";
        std::getline(cin, arr[i].str);
        cout << "Enter data for integer field: ";
        cin >> arr[i].val;
      }
      cout << "Error expected" << endl;

      // insertionSort(arr, value);

      // If the comment is taken out, code will not compile since ">" operator
      // used in the insertionSort() function is not defined for structures.
      remove(arr);
      break;
    }

    case 6: {
      flag = false;
      break;
    }

    default:
      cout << "Enter valid option" << endl;
    }
  }
  return 0;
}
