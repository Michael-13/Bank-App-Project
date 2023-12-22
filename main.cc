#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>
#include <memory>
#include "database.h"
#include "account.h"
#include "except.h"

int main(int argc, char *argv[]) {
    std::string cmd;
    bool admin = false;
    bool login = false;
    // handle flags
    for (int i = 1; i < argc; ++i) {
        try {
            if (std::strcmp(argv[i], "-admin") == 0) {
                admin = true;
            } else {
                cmd = argv[i];
                throw invalidArg();
            }
        } catch(invalidArg &i) {
            std::cerr << cmd << " is not a valid argument" << std::endl;
            return 1;
        }
    }

    std::shared_ptr<DataBase> db{new DataBase{"DB.csv"}};
    Account profile{db};
    while(true) {
        if (admin) {
            std::cin >> cmd;
            if (cmd == "add") {
                db->addAccount();
            } else if (cmd == "remove") {
                std::cout << "Please enter the username of the account you would like to remove: ";
                std::string un;
                std::cin >> un;
                db->removeAccount(un);
            } else if (cmd == "quit") {
                break;
            }
        } else {
            if (!login) {
                std::vector<std::string> info;
                while(true) {
                    std::string un;
                    std::cout << "Enter Username: ";
                    std::cin >> un;
                    if (std::cin.eof()) break;
                    try {
                        info = db->getAccInfo(un);
                        std::string pw;
                        std::cout << "Enter Password: ";
                        std::cin >> pw;
                        if (std::cin.eof()) break;
                        if (pw == info[1]) {
                            login = true;
                            profile.attachInfo(info);
                        } else {
                            throw IncorrectPassword();
                        }
                        break;
                    } catch (UsernameNotFound &u) {
                        std::cout << "Username not found, please try again. ";
                        continue;
                    } catch (IncorrectPassword &p) {
                        std::cout << "Password incorrect please try again. ";
                        continue;
                    }
                }
                if (std::cin.eof()) break;
                login = true;
            }
            std::cin >> cmd;
            if (cmd == "print") {
                std::cout << profile << std::endl;
            } else if (cmd == "deposit") {
                float cash;
                std::cin >> cash; 
                profile.deposit(cash);
            } else if (cmd == "withdraw") {
                float cash;
                std::cin >> cash;
                profile.withdraw(cash);
            } else if (cmd == "quit") {
                break;
            }
        }
    }
    return 0;
}