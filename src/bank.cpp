#include "bank.h"

Bank::Bank() {}

Account &Bank::create_account(std::string name, double amount) {
  Account account = Account(name, amount);
  this->accounts.emplace(name, account);
  return this->accounts.at(name);
}

Account &Bank::get_account(const std::string &name) {
  return this->accounts.at(name);
}

bool Bank::account_exists(const std::string &name) const {
  return this->accounts.count(name) > 0;
}
