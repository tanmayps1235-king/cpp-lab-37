
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

class Account {
protected:
    string name;
    int accountNumber;
    double balance;
    vector<string> transactions;

public:
    Account(string n, int accNo, double bal) {
        name = n;
        accountNumber = accNo;
        balance = bal;
        transactions.push_back("Account opened");
    }

    virtual void deposit(double amount) {
        if (amount <= 0) {
            cout << "Invalid deposit amount!\n";
            return;
        }

        balance += amount;
        transactions.push_back("Deposited: Rs. " +
                               to_string(amount));
        cout << "Deposit successful!\n";
    }

    virtual void withdraw(double amount) {
        if (amount <= 0) {
            cout << "Invalid withdrawal amount!\n";
        }
        else if (amount > balance) {
            cout << "Insufficient balance!\n";
        }
        else {
            balance -= amount;
            transactions.push_back("Withdrawn: Rs. " +
                                   to_string(amount));
            cout << "Withdrawal successful!\n";
        }
    }

    virtual void displayStatement() {
        cout << "\n----- Account Statement -----\n";
        cout << "Name: " << name << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << fixed << setprecision(2);
        cout << "Current Balance: Rs. " << balance << endl;

        cout << "\nTransaction History:\n";
        for (const string& t : transactions) {
            cout << t << endl;
        }
    }

    virtual ~Account() {}
};

class SavingsAccount : public Account {
public:
    SavingsAccount(string n, int accNo, double bal)
        : Account(n, accNo, bal) {}

    void displayStatement() override {
        cout << "\nAccount Type: Savings Account\n";
        Account::displayStatement();
    }
};

class CheckingAccount : public Account {
public:
    CheckingAccount(string n, int accNo, double bal)
        : Account(n, accNo, bal) {}

    void displayStatement() override {
        cout << "\nAccount Type: Checking Account\n";
        Account::displayStatement();
    }
};

int main() {
    int type, choice, accNo;
    string name;
    double balance, amount;

    cout << "----- Banking System -----\n";
    cout << "1. Savings Account\n";
    cout << "2. Checking Account\n";
    cout << "Choose account type: ";
    cin >> type;

    cout << "Enter account holder name: ";
    getline(cin >> ws, name);

    cout << "Enter account number: ";
    cin >> accNo;

    cout << "Enter initial balance: ";
    cin >> balance;

    if (balance < 0) {
        cout << "Initial balance cannot be negative!\n";
        return 0;
    }

    Account* account = nullptr;

    if (type == 1) {
        account = new SavingsAccount(name, accNo, balance);
    }
    else if (type == 2) {
        account = new CheckingAccount(name, accNo, balance);
    }
    else {
        cout << "Invalid account type!\n";
        return 0;
    }

    do {
        cout << "\n----- Banking Menu -----\n";
        cout << "1. Deposit\n";
        cout << "2. Withdraw\n";
        cout << "3. Account Statement\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter deposit amount: ";
            cin >> amount;
            account->deposit(amount);
            break;

        case 2:
            cout << "Enter withdrawal amount: ";
            cin >> amount;
            account->withdraw(amount);
            break;

        case 3:
            account->displayStatement();
            break;

        case 4:
            cout << "Thank you for using our bank!\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 4);

    delete account;
    return 0;
}
