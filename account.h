#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "database.h"

class Account {
    std::shared_ptr<DataBase> db;
    std::vector<std::string> info;

    public:
        Account(std::shared_ptr<DataBase> db);
        ~Account();

        void attachInfo(std::vector<std::string> &i);
        void deposit(float &cash);
        void withdraw(float &cash);

        friend std::ostream &operator<<(std::ostream &out, Account &a);
};

#endif
