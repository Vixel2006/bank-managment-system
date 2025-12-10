#include "account.h"
#include <iostream>

void Account::deposit(double amount) {
  *this += amount;
  std::cout << "[+] Deposited " << amount << " into " << name_
            << ". Total account balance now = " << balance_ << std::endl;
}

void Account::withdraw(double amount) {
  if (balance_ - amount < 0) {
    std::cout << "[ERR] [-] Cannot withdraw the amount " << amount
              << " from account " << name_ << " as current balance is "
              << balance_ << std::endl;
    return;
  }

  *this -= amount;
  std::cout << "[-] Withdrew " << amount << " from " << name_
            << ". Total account balance now = " << balance_ << std::endl;
}

void Account::transfer(double amount, Account &reciever) {
  if (balance_ - amount < 0) {
    std::cout << "[ERR] [>] Cannot transfer the amount " << amount
              << " from account " << name_ << " as current balance is "
              << balance_ << std::endl;
    return;
  }

  *this -= amount;
  reciever += amount;

  std::cout << "[>] Transferred " << amount << " from " << name_ << " into "
            << reciever.get_name() << std::endl;
}
