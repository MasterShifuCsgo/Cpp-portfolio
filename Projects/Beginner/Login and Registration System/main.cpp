
#include <iostream>
#include <fstream>
#include "regsys.h"

int main(){

    system("cls");
    std::cout << "hello user, Welcome to login and registration system Program\n";

    std::string filename{"datafile.txt"};

    std::string username{};
    std::string password{};

    RegSys::askUserInfo(username, password);
    bool isUserfound = RegSys::searchUserInfo(filename, username, password);
    
    if(isUserfound){
        RegSys::userLogin();
    }else{
        bool isCompleted = RegSys::registerUser(filename, username, password);
        if(isCompleted){
            std::cout << "<< You have been registered - Try to Log in >>";
        }
    }


    return 0;
}












