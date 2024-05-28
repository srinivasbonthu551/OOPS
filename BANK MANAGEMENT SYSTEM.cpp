#include <iostream>
#include <vector>
#include <string>

class BankAccount {
public:
    BankAccount(std::string accountHolderName, std::string accountNumber, double balance)
        : accountHolderName(accountHolderName), accountNumber(accountNumber), balance(balance) {}

    void deposit(double amount) {
        balance += amount;
        std::cout << "Deposited: $" << amount << "\n";
    }

    void withdraw(double amount) {
        if (amount > balance) {
            std::cout << "Insufficient funds.\n";
        } else {
            balance -= amount;
            std::cout << "Withdrew: $" << amount << "\n";
        }
    }

    void displayAccountDetails() const {
        std::cout << "Account Holder: " << accountHolderName << "\n";
        std::cout << "Account Number: " << accountNumber << "\n";
        std::cout << "Balance: $" << balance << "\n";
    }

    std::string getAccountNumber() const {
        return accountNumber;
    }

private:
    std::string accountHolderName;
    std::string accountNumber;
    double balance;
};

class Bank {
public:
    void createAccount(std::string accountHolderName, std::string accountNumber, double initialDeposit) {
        accounts.push_back(BankAccount(accountHolderName, accountNumber, initialDeposit));
        std::cout << "Account created successfully.\n";
    }

    void depositToAccount(std::string accountNumber, double amount) {
        BankAccount* account = findAccount(accountNumber);
        if (account) {
            account->deposit(amount);
        } else {
            std::cout << "Account not found.\n";
        }
    }

    void withdrawFromAccount(std::string accountNumber, double amount) {
        BankAccount* account = findAccount(accountNumber);
        if (account) {
            account->withdraw(amount);
        } else {
            std::cout << "Account not found.\n";
        }
    }

    void displayAccountDetails(std::string accountNumber) const {
        const BankAccount* account = findAccount(accountNumber);
        if (account) {
            account->displayAccountDetails();
        } else {
            std::cout << "Account not found.\n";
        }
    }

private:
    std::vector<BankAccount> accounts;

    BankAccount* findAccount(std::string accountNumber) {
        for (std::vector<BankAccount>::iterator it = accounts.begin(); it != accounts.end(); ++it) {
            if (it->getAccountNumber() == accountNumber) {
                return &(*it);
            }
        }
        return NULL;
    }

    const BankAccount* findAccount(std::string accountNumber) const {
        for (std::vector<BankAccount>::const_iterator it = accounts.begin(); it != accounts.end(); ++it) {
            if (it->getAccountNumber() == accountNumber) {
                return &(*it);
            }
        }
        return NULL;
    }
};

int main() {
    Bank bank;
    int choice;
    std::string accountHolderName, accountNumber;
    double amount;

    while (true) {
        std::cout << "\nBank Account Management System\n";
        std::cout << "1. Create Account\n";
        std::cout << "2. Deposit Money\n";
        std::cout << "3. Withdraw Money\n";
        std::cout << "4. View Account Details\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter Account Holder Name: ";
                std::cin.ignore(); // To clear the input buffer
                std::getline(std::cin, accountHolderName);
                std::cout << "Enter Account Number: ";
                std::cin >> accountNumber;
                std::cout << "Enter Initial Deposit: ";
                std::cin >> amount;
                bank.createAccount(accountHolderName, accountNumber, amount);
                break;

            case 2:
                std::cout << "Enter Account Number: ";
                std::cin >> accountNumber;
                std::cout << "Enter Amount to Deposit: ";
                std::cin >> amount;
                bank.depositToAccount(accountNumber, amount);
                break;

            case 3:
                std::cout << "Enter Account Number: ";
                std::cin >> accountNumber;
                std::cout << "Enter Amount to Withdraw: ";
                std::cin >> amount;
                bank.withdrawFromAccount(accountNumber, amount);
                break;

            case 4:
                std::cout << "Enter Account Number: ";
                std::cin >> accountNumber;
                bank.displayAccountDetails(accountNumber);
                break;

            case 5:
                std::cout << "Exiting...\n";
                return 0;

            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    return 0;
}

