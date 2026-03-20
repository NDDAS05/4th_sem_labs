#include <iostream>
#include <string>
using namespace std;

// Base class: BankAccount
class BankAccount {
  string account_no;
  string holder_name;
  double balance;
  static int account_count;

public:
  BankAccount(const string &acc_no, const string &name, const double &balance)
      : account_no(acc_no), holder_name(name), balance(balance) {
    account_count++;
  }
  ~BankAccount() { account_count--; }

  string getAccountNo() const { return account_no; }

  friend class BankManager;
};

int BankAccount::account_count = 0;

// Manager class
class BankManager {
public:
  int accountCount() { return BankAccount::account_count; }
  void display(const BankAccount &obj) {
    cout << "Details for A/C No: " << obj.account_no << endl
         << "------------------------------------" << endl;
    cout << "\tHolder Name: " << obj.holder_name << endl;
    cout << "\tAvailable Balance: " << obj.balance << endl;
  }

  bool hasSufficientBalance(const BankAccount &obj, double debit_amt) {
    if ((obj.balance) - debit_amt >= 0 && obj.balance != 0)
      return true;
    return false;
  }

  bool transferBalance(BankAccount &source, BankAccount &destination,
                       double debit_amount) {
    if (hasSufficientBalance(source, debit_amount) &&
        (&source != &destination)) {
      source.balance = source.balance - debit_amount;
      destination.balance = destination.balance + debit_amount;

      return true;
    }
    return false;
  }
};

int findAccountIndex(BankAccount *accounts[], int current_count,
                     const string &search_acc_no) {
  for (int i = 0; i < current_count; i++) {
    if (accounts[i]->getAccountNo() == search_acc_no) {
      return i;
    }
  }
  return -1;
}

int main() {
  BankManager manager;
  BankAccount *accounts[100];
  int current_index = 0;
  int choice;

  while (true) {
    cout << "\n" << endl;
    cout << "Choose option: " << endl;
    cout << "===================================" << endl;
    cout << "1. Open New Account" << endl;
    cout << "2. Display Account Details" << endl;
    cout << "3. Transfer Funds" << endl;
    cout << "4. View Total Active Accounts" << endl;
    cout << "5. Exit" << endl;
    cout << "-----------------------------------" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 5) {
      cout << "Releasing resources..." << endl;
      for (int i = 0; i < current_index; i++) {
        delete accounts[i];
      }
      break;
    }

    switch (choice) {
    case 1: {
      if (current_index >= 100) {
        cout << "Maximum Capacity Reached" << endl;
        break;
      }
      string acc_no, name;
      double bal;

      cout << "\nOpen New Account\n--------------------------" << endl;
      cout << "Enter Account Number: ";
      cin >> acc_no;

      if (findAccountIndex(accounts, current_index, acc_no) != -1) {
        cout << "Error: Account number " << acc_no << " already exists."
             << endl;
        break;
      }

      cin.ignore();
      cout << "Enter Holder Name: ";
      getline(cin, name);
      cout << "Enter Initial Balance: ";
      cin >> bal;

      accounts[current_index] = new BankAccount(acc_no, name, bal);
      current_index++;
      cout << "Account created successfully." << endl;
      break;
    }

    case 2: {
      cout << "\nDisplay Account\n--------------------------" << endl;
      if (current_index == 0) {
        cout << "Record empty." << endl;
        break;
      }

      string search_acc;
      cout << "Enter Account Number to search: ";
      cin >> search_acc;

      int idx = findAccountIndex(accounts, current_index, search_acc);

      if (idx != -1) {
        manager.display(*accounts[idx]);
      } else {
        cout << "Error: Account not found." << endl;
      }
      break;
    }

    case 3: {
      cout << "\nTransfer Funds\n--------------------------" << endl;
      if (current_index < 2) {
        cout << "At least 2 accounts required for fund transfer." << endl;
        break;
      }

      string src_acc, dest_acc;
      double amount;

      cout << "Enter Source Account Number: ";
      cin >> src_acc;
      cout << "Enter Destination Account Number: ";
      cin >> dest_acc;

      int src_idx = findAccountIndex(accounts, current_index, src_acc);
      int dest_idx = findAccountIndex(accounts, current_index, dest_acc);

      if (src_idx == -1) {
        cout << "Error: Source account not found." << endl;
        break;
      }
      if (dest_idx == -1) {
        cout << "Error: Destination account not found." << endl;
        break;
      }

      cout << "Enter Amount to Transfer: ";
      cin >> amount;

      bool success = manager.transferBalance(*accounts[src_idx],
                                             *accounts[dest_idx], amount);

      if (success) {
        cout << "Transfer successful." << endl;
      } else {
        cout << "Transfer failed. Check balance or ensure accounts are "
                "different."
             << endl;
      }
      break;
    }

    case 4: {
      cout << "\nTotal Active Accounts: " << manager.accountCount() << endl;
      break;
    }

    default:
      cout << "Invalid choice." << endl;
    }
  }
  return 0;
}
