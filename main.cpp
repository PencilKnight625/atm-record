#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <algorithm>


using namespace std;

class Account 
{
private:
    string name;
    string accountNumber;
    string pin;
    double balance;
    vector<string> transactions;

    string getFileName() const 
    {
        return "account_" + accountNumber + ".txt";
    }

public:
    Account() : balance(0.0) {}

    void createNewAccount(string userName, string pinCode, string accNum) 
    {
        name = userName;
        pin = pinCode;
        accountNumber = accNum;
        balance = 0.0;
        saveToFile();
    }

    bool verifyPIN(const string& inputPin) 
    {
        return inputPin == pin;
    }

    //DEPOSIT
    void deposit(double amount) 
    {
        balance += amount;
        stringstream ss;
        ss << "+ Rs " << fixed << setprecision(2) << amount << " (Deposit)";
        transactions.push_back(ss.str());
        cout << "Deposit successful.\n";
    }

    //WITHDRAWL
    bool withdraw(double amount) 
    {
        if (amount > balance) 
        {
            cout << "Insufficient balance.\n";
            return false;
        }
        balance -= amount;
        stringstream ss;
        ss << "- Rs " << fixed << setprecision(2) << amount << " (Withdrawal)";
        transactions.push_back(ss.str());
        cout << "Withdrawal successful.\n";
        return true;
    }

    //BALANCE CHECK
    void checkBalance() const 
    {
        cout << "Current Balance: Rs " << fixed << setprecision(2) << balance << "\n";
    }

    //TRANSACTION HISTORY
    void showTransactions() const 
    {
        if (transactions.empty()) 
        {
            cout << "No transactions yet.\n";
            return;
        }

        cout << "\n--- Transaction History ---\n";
        for (const string& t : transactions)
            cout << t << "\n";
        cout << "---------------------------\n";
    }

    //FILE SAVE
    void saveToFile() 
    {
        ofstream file(getFileName());
        if (file.is_open()) 
        {
            file << name << "\n";
            file << accountNumber << "\n";
            file << pin << "\n";
            file << balance << "\n";
            for (const string& t : transactions)
                file << t << "\n";
            file.close();
        }
    }

    bool loadFromFile(const string& accNum) 
    {
        ifstream file("account_" + accNum + ".txt");
        if (!file.is_open()) return false;

        accountNumber = accNum;
        string line;
        getline(file, name);
        getline(file, accountNumber);
        getline(file, pin);
        file >> balance;
        file.ignore();             
        transactions.clear();
        while (getline(file, line)) 
        {
            transactions.push_back(line);
        }
        file.close();
        return true;
    }

    string getAccountNumber() const { return accountNumber; }
    string getName() const { return name; }
};

// Generate unique account number
string generateAccountNumber() 
{
    ifstream infile("last_account.txt");
    int lastAcc = 10101;
    if (infile >> lastAcc) 
    {
        lastAcc=lastAcc+4;
    }
    infile.close();

    ofstream outfile("last_account.txt");
    outfile << lastAcc;
    outfile.close();

    return to_string(lastAcc);
}

void pause() 
{
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

void atmMenu(Account& acc) 
{
    int choice;
    double amount;
    do {
        cout << "\n====== ATM MENU ======\n";
        cout << "1. Check Balance\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. View Transactions\n";
        cout << "5. Exit\n";
        cout << "Choose option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                acc.checkBalance();
                break;
            case 2:
                cout << "Enter amount to deposit: Rs ";
                cin >> amount;
                acc.deposit(amount);
                break;
            case 3:
                cout << "Enter amount to withdraw: Rs ";
                cin >> amount;
                acc.withdraw(amount);
                break;
            case 4:
                acc.showTransactions();
                break;
            case 5:
                acc.saveToFile();
                cout << "Session saved. Thankyou for Using. Goodbye! :)\n";
                break;
            default:
                cout << "Invalid option. Try again :(\n";
        }
    } while (choice != 5);
}

int main() 
{
    char choice;
    cout << "=== Welcome to MY ATM ===\n";
    cout << "Do you have an existing account? (Y/N): ";
    cin >> choice;

    Account user;
    string accNum, pin;

    if (toupper(choice) == 'Y') 
    {
        cout << "Enter Account Number: ";
        cin >> accNum;
        if (!user.loadFromFile(accNum)) 
        {
            cout << "Account not found  :( \n";
            return 0;
        }

        cout << "Enter PIN: ";
        cin >> pin;
        if (user.verifyPIN(pin)) 
        {
            cout << "Login successful. Welcome, :)" << user.getName() << "!\n";
            atmMenu(user);
        } 
        else 
        {
            cout << "Incorrect PIN  :( \n";
        }

    } 
    else 
    {
        string name, newPin;
        cin.ignore();
        cout << "Enter your name: ";
        getline(cin, name);
        cout << "Set a 4-digit PIN: ";
        cin >> newPin;

        if (newPin.length() != 4 || !all_of(newPin.begin(), newPin.end(), ::isdigit)) 
        {
            cout << "Invalid PIN. Must be exactly 4 digits :( \n";
            return 0;
        }

        string newAccNum = generateAccountNumber();
        user.createNewAccount(name, newPin, newAccNum);
        cout << "Account created successfully!\n";
        cout << "Your account number is: " << newAccNum << "\n";
        pause();
        atmMenu(user);
    }

    return 0;
}
