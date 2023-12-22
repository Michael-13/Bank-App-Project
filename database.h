#ifndef __DATABASE_H__
#define __DATABASE_H__
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

class DataBase {
    std::string file;

    public:
        DataBase(std::string file);
        ~DataBase();

        void addAccount();
        void removeAccount(const std::string &un);
        void adjustAccBalance(const std::string &un, const std::string &bal);
        std::vector<std::string> getAccInfo(const std::string &un) const;
};

#endif
