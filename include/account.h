#pragma once

#include <string>

class Account {
  std::string name_;
  double balance_;

public:
  Account(std::string name, double balance) : name_(name), balance_(balance) {}
  ~Account() = default;

  std::string get_name() const { return name_; }
  double get_balance() const { return balance_; }

  Account &operator+=(double amount) {
    this->balance_ += amount;
    return *this;
  }

  Account &operator-=(double amount) {
    this->balance_ -= amount;
    return *this;
  }

  void deposit(double amount);
  void withdraw(double amount);
  void transfer(double amount, Account &reciever);
};
