# ATM Simulator in C++
# Description
This is a console-based ATM Simulator built in C++. It allows users to securely create and manage personal bank accounts using a unique account number and a 4-digit PIN.
The system supports key banking operations such as deposit, withdrawal, balance inquiry, and transaction history, all saved using file-based persistence.

* Features
* Account Creation with Auto-Generated Unique Account Number
* PIN-Based Secure Login
* Deposit & Withdrawal Functionality
* Balance Check
* Transaction History Tracking
* Persistent File Storage for Each User
* Object-Oriented Design using C++ Classes
* Input Validation (PIN, amounts)

# How It Works
On first use, users can create a new account with:
Their name
A valid 4-digit PIN
The program generates and shows a unique account number
Existing users can log in using:
Account number
PIN
User actions are saved in a file named like account_10001.txt, storing:
Name, PIN, balance, and full transaction history

# How to Run
bash
g++ main.cpp -o atm
