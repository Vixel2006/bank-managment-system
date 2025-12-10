#include "account.h"
#include "bank.h"
#include <iostream>
#include <limits> // Required for numeric_limits

void clear_input_buffer() {
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void print_menu() {
  std::cout << "\n--- Bank Application Menu ---\n";
  std::cout << "1. Create Account\n";
  std::cout << "2. Deposit\n";
  std::cout << "3. Withdraw\n";
  std::cout << "4. Transfer\n";
  std::cout << "5. View Account Balance\n";
  std::cout << "6. List All Accounts\n";
  std::cout << "7. Exit\n";
  std::cout << "Enter your choice: ";
}

int main() {
  Bank bank;
  int choice;
  std::string account_name;
  double amount;
  std::string target_account_name;

  do {
    print_menu();
    std::cin >> choice;

    // Handle invalid input for choice
    if (std::cin.fail()) {
      std::cout << "Invalid input. Please enter a number.\n";
      std::cin.clear();     // Clear error flags
      clear_input_buffer(); // Discard invalid input
      continue;
    }
    clear_input_buffer(); // Clear the rest of the line after reading choice

    switch (choice) {
    case 1: // Create Account
      std::cout << "Enter new account name: ";
      std::getline(std::cin, account_name);
      if (bank.account_exists(account_name)) {
        std::cout << "Account with name '" << account_name
                  << "' already exists.\n";
      } else {
        std::cout << "Enter initial balance: ";
        std::cin >> amount;
        if (std::cin.fail() || amount < 0) {
          std::cout << "Invalid amount. Please enter a non-negative number.\n";
          std::cin.clear();
          clear_input_buffer();
          break;
        }
        clear_input_buffer();
        bank.create_account(account_name, amount);
        std::cout << "Account '" << account_name << "' created with balance "
                  << amount << ".\n";
      }
      break;
    case 2: // Deposit
      std::cout << "Enter account name to deposit into: ";
      std::getline(std::cin, account_name);
      if (bank.account_exists(account_name)) {
        std::cout << "Enter amount to deposit: ";
        std::cin >> amount;
        if (std::cin.fail() || amount < 0) {
          std::cout << "Invalid amount. Please enter a non-negative number.\n";
          std::cin.clear();
          clear_input_buffer();
          break;
        }
        clear_input_buffer();
        bank.get_account(account_name).deposit(amount);
      } else {
        std::cout << "Account '" << account_name << "' not found.\n";
      }
      break;
    case 3: // Withdraw
      std::cout << "Enter account name to withdraw from: ";
      std::getline(std::cin, account_name);
      if (bank.account_exists(account_name)) {
        std::cout << "Enter amount to withdraw: ";
        std::cin >> amount;
        if (std::cin.fail() || amount < 0) {
          std::cout << "Invalid amount. Please enter a non-negative number.\n";
          std::cin.clear();
          clear_input_buffer();
          break;
        }
        clear_input_buffer();
        bank.get_account(account_name).withdraw(amount);
      } else {
        std::cout << "Account '" << account_name << "' not found.\n";
      }
      break;
    case 4: // Transfer
      std::cout << "Enter source account name: ";
      std::getline(std::cin, account_name);
      if (!bank.account_exists(account_name)) {
        std::cout << "Source account '" << account_name << "' not found.\n";
        break;
      }
      std::cout << "Enter target account name: ";
      std::getline(std::cin, target_account_name);
      if (!bank.account_exists(target_account_name)) {
        std::cout << "Target account '" << target_account_name
                  << "' not found.\n";
        break;
      }
      if (account_name == target_account_name) {
        std::cout << "Cannot transfer to the same account.\n";
        break;
      }
      std::cout << "Enter amount to transfer: ";
      std::cin >> amount;
      if (std::cin.fail() || amount < 0) {
        std::cout << "Invalid amount. Please enter a non-negative number.\n";
        std::cin.clear();
        clear_input_buffer();
        break;
      }
      clear_input_buffer();
      bank.get_account(account_name)
          .transfer(amount, bank.get_account(target_account_name));
      break;
    case 5: // View Account Balance
      std::cout << "Enter account name to view balance: ";
      std::getline(std::cin, account_name);
      if (bank.account_exists(account_name)) {
        std::cout << "Account '" << account_name << "' balance: "
                  << bank.get_account(account_name).get_balance() << ".\n";
      } else {
        std::cout << "Account '" << account_name << "' not found.\n";
      }
      break;
    case 6: // List All Accounts
      if (bank.accounts.empty()) {
        std::cout << "No accounts created yet.\n";
      } else {
        std::cout << "\n--- All Accounts ---\n";
        for (const auto &pair : bank.accounts) {
          std::cout << "Account: " << pair.second.get_name()
                    << ", Balance: " << pair.second.get_balance() << "\n";
        }
        std::cout << "--------------------\n";
      }
      break;
    case 7: // Exit
      std::cout << "Exiting Bank Application. Goodbye!\n";
      break;
    default:
      std::cout << "Invalid choice. Please try again.\n";
      break;
    }
  } while (choice != 7);

  return 0;
}
