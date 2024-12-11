#ifndef __REGSYS_H__
#define __REGSYS_H__

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

namespace RegSys {

    // Removes spaces from a string
    void removeSpaces(std::string &var) {
        var.erase(std::remove(var.begin(), var.end(), ' '), var.end());
    }

    // Prompts user for username and password
    void askUserInfo(std::string &username, std::string &password) {
        std::cout << "-- Username: ";
        std::getline(std::cin, username);
        std::cout << "-- Password: ";
        std::getline(std::cin, password);
        removeSpaces(username);
        removeSpaces(password);
    }

    // Searches for a user in the file
    bool searchUserInfo(const std::string &fileName, const std::string &username, const std::string &password) {
        std::ifstream data(fileName);

        if (!data.is_open()) {
            throw std::ios_base::failure("Error: Unable to open file for reading.");
        }

        std::string line;
        while (std::getline(data, line)) {
            // Each line is in the format "username:password"
            auto delimiterPos = line.find(':');
            if (delimiterPos == std::string::npos) {
                continue; // Invalid format, skip this line
            }

            std::string fileUsername = line.substr(0, delimiterPos);
            std::string filePassword = line.substr(delimiterPos + 1);

            if (fileUsername == username && filePassword == password) {
                return true; // Match found
            }
        }

        return false; // No match found
    }

    // Logs user in
    void userLogin() {
        std::cout << "\n<< You've logged in >>\n";
    }

    // Registers a new user in the file
    bool registerUser(const std::string &fileName, const std::string &username, const std::string &password) {
        std::ofstream writefile(fileName, std::ios::app);

        if (!writefile.is_open()) {
            throw std::ios_base::failure("Error: Unable to open file for writing.");
        }

        writefile << username << ':' << password << '\n';
        return true;
    }

} // namespace RegSys

#endif // __REGSYS_H__
