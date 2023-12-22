#include "database.h"
#include "except.h"

DataBase::DataBase(std::string file) : file{file} {}

DataBase::~DataBase() {}

void DataBase::addAccount() {
    std::string username, password, name, accBal;
    // get all account information
    std::cout << "Username: ";
    std::cin >> username;
    std::cout << "Password: ";
    std::cin >> password;
    std::cout << "Client's Name: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    while (true) {
        std::cout << "Balance: "; 
        std::cin >> accBal;
        try {
            float bal = std::stof(accBal);
            accBal = std::to_string(bal);
            break;
        } catch (std::invalid_argument &a) {
            std::cout << "you have not entered a valid balance please try again" << std::endl;
            continue;
        }
    }
    std::ofstream file;
    file.open("DB.csv", std::ios_base::app);
    file << username << "," << password << "," << name << "," << accBal << std::endl;
    file.close();
}

void DataBase::removeAccount(const std::string &un) {
    std::ofstream temp;
    temp.open("temp.csv", std::ios_base::app);
    std::ifstream file;
    file.open("DB.csv");
    std::string username, password, accName, accBal;
    while(std::getline(file, username, ',')) {
        std::getline(file, password, ',');
        std::getline(file, accName, ',');
        std::getline(file, accBal, '\n');
        if (username == un) continue;
        temp << username << "," << password << "," << accName << "," << accBal << "\n"; 
    }
    file.close();
    std::remove("DB.csv");
    temp.close();
    std::rename("temp.csv", "DB.csv");
}

void DataBase::adjustAccBalance(const std::string &un, const std::string &bal) {
    std::ofstream temp;
    temp.open("temp.csv", std::ios_base::app);
    std::ifstream file;
    file.open("DB.csv");
    std::string username, password, accName, accBal;
    while(std::getline(file, username, ',')) {
        std::getline(file, password, ',');
        std::getline(file, accName, ',');
        std::getline(file, accBal, '\n');
        if (username == un) {
            temp << username << "," << password << "," << accName << "," << bal << "\n";
            continue;
        }
        temp << username << "," << password << "," << accName << "," << accBal << "\n"; 
    }
    file.close();
    std::remove("DB.csv");
    temp.close();
    std::rename("temp.csv", "DB.csv");
}

std::vector<std::string> DataBase::getAccInfo(const std::string &un) const {
    std::vector<std::string> info;
    bool found = false;

    std::ifstream file;
    file.open("DB.csv");
    std::string username, password, accName, accBal;
    while(std::getline(file, username, ',')) {
        std::getline(file, password, ',');
        std::getline(file, accName, ',');
        std::getline(file, accBal, '\n');    
        if (username == un) {
            found = true;
            info.push_back(username);
            info.push_back(password);
            info.push_back(accName);
            info.push_back(accBal);
            break;
        }
    }

    if (!found) throw UsernameNotFound();
    return info;
}