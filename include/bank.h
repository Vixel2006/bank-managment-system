#pragma once

#include "account.h"
#include <unordered_map>
#include <vector>

class Bank {
public:
  std::unordered_map<std::string, Account> accounts;

  Bank();
  ~Bank() = default;

  bool account_exists(const std::string &name) const;
  Account &get_account(const std::string &name);
  Account &create_account(std::string name, double amount);
};
