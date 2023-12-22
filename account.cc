#include "account.h"

Account::Account(std::shared_ptr<DataBase> db) : db{db} {}
Account::~Account() {}

void Account::attachInfo(std::vector<std::string> &i) {
    info = i;
}

void Account::deposit(float &cash) {
    float temp = std::stof(info[3]);
    temp += cash;
    std::string bal = std::to_string(temp);
    info[3] = bal;
    db->adjustAccBalance(info[0], bal);
}

void Account::withdraw(float &cash) {
    float temp = std::stof(info[3]);
    temp -= cash;
    std::string bal = std::to_string(temp);
    info[3] = bal;
    db->adjustAccBalance(info[0], bal);
}

std::ostream &operator<<(std::ostream &out, Account &a) {
    out << "Account Name: " << a.info[2] << std::endl; 
    out << "Account Balance: " << a.info[3];
    return out;
}