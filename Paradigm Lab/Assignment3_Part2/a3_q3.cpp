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
    cout << "Holder Name: " << obj.holder_name << endl;
    cout << "Available Balance: " << obj.balance << endl;
  }

  bool hasSufficientBalance(const BankAccount &obj, int debit_amt) {}
};
