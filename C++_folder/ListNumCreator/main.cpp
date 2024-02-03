
#include <iostream>
#include <fstream> // gives access to ifsteam objs
#include <string>

int main(){

std::fstream Datafile; //our cin
std::fstream Writefile;
// attempt to open the file. 

Datafile.open("dataToBeConverted.txt"); // you do .close() after using it

// verify the file opened.

if(Datafile.is_open() ){


// std::cin >> x; read data from the terminal. what you put in the terminal.
// std::cin >> x >> y >> z; // 12 33 54 gets the data as long as its seperated by whitespace(s). x will be 12 and so on...

size_t count{0};

std::string toIgnore[] = {"Beginners Level", "Intermediate Level", "Expert Level"};

    unsigned int projects{1};
    unsigned int total{0};
    std::string line;


    for(size_t i = 0; std::getline(Datafile, line);){
            if(line.find(toIgnore[i]) != std::string::npos){
                
                // if "1" is any higher, glitches start happening, figure out why.

                i <= 1 ? i++ : 0;
                std::cout << '\t'<< line << '\n';
                total += projects;
                projects = 0;

                // EXplenation 
                /*

                
                */
            }else{

            std::cout << projects << ". " << line << '\n';
            }

            projects++;
    }
    std::cout << "\nTotal amount of projects is " << total << std::endl;
Datafile.close();

}else{
    std::cout << "File dosen't exist in directory";
 }
}
