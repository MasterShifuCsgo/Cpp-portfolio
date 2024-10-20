#ifndef __REGSYS_H__
#define __REGSYS_H__

#include <string>
#include <iostream>
#include <fstream>

void remove_spaces(std::string &var){
        for(int i{}; i < var.size(); i++){
            if(var[i] == ' '){
                var[i] = '\0';
            }
        }
};

namespace RegSys{

    void askUserInfo(std::string &username, std::string &password){
        
        std::cout << "-- Username: ";
        std::getline(std::cin, username);
        std::cout << "-- Password: ";
        std::getline(std::cin, password);
        remove_spaces(username);
        remove_spaces(password);
    }

    bool searchUserInfo(std::string &fileName, std::string &username, std::string &password){

        //opens datafile or creates it if it doesnt exist.
        std::fstream data;
        data.open(fileName, std::ios::out | std::ios::in);

        if(!data.is_open()){
            std::cout << "Error Opening file.\n";
            std::cout << "File should have been created. Try again.";
            exit(1);
        }

        // search for username and password fields
        /* 
        format in the file: 
        username:password
        username:password
        username:password
        */

        std::string line {};
        bool readPassword{false};
        
        int count{};
        while(getline(data, line)){
            
            if(!(line.size() == (username.size() + password.size() + 1))){
                continue;
            }

            count = 0;

            for(int i{}; i < line.size(); i++){
                // checks if username exists
                if(!readPassword){
                    if(username[i] != line[i] && line[i] != ':'){
                        break;
                    }else if(line[i] == ':'){
                        bool readPassoword = true;
                    }
                }

                //if username is found checks the password
                if(line[i] == password[i]){
                    count++;
                    if(count == password.size()){
                        data.close();
                        return true; // if password is the same send true, meaning that it had found the user.
                    }
                }
            }
        }
        data.close();
        return false;
    }

    void userLogin(){
        std::cout << "\n<< You've logged in >>\n";
    }

    bool registerUser(std::string &fileName, std::string &username, std::string &password){
        //opens datafile or creates it if it doesnt exist.
        std::fstream writefile;
        writefile.open(fileName, std::ios::app);

        if(!writefile.is_open()){
            std::cout << "Error Opening file.";
            return false;
        }

        writefile << username << ':' << password << '\n';

        writefile.close();
        return true;
    }
}

#endif // __REGSYS_H__