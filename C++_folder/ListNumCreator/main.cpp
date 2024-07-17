#include <iostream>
#include <fstream> // gives access to ifsteam objs
#include <string>
#include <cstdio>
#include "WriteFileFunc.h"


int main(){

std::fstream Datafile; //our cin
// attempt to open the file. 

Datafile.open("dataToBeConverted.txt"/*can put more parameters, opens in read mode, not write*/); // you do .close() after using it



// verify the file opened.

if(Datafile.is_open() ){

// std::cin >> x; read data from the terminal. what you put in the terminal.
// std::cin >> x >> y >> z; // 12 33 54 gets the data as long as its seperated by whitespace(s). x will be 12 and so on...

size_t count{0};

std::string toIgnore[] = {"Beginners Level", "Intermediate Level", "Expert Level"};

    unsigned int projects{1};
    unsigned int total{0};
    std::string line;

//user modifiable variables
const char* Filename{"Newfile.txt"};

if(std::remove( Filename ) == 0){
    puts( "File successfully deleted" );
}else{
    perror( "Error deleting file" );
}


    for(size_t i = 0; std::getline(Datafile, line);){

            if(line.find(toIgnore[i]) == 0){
                
                i < 2 ? i++ : 0;
               // std::cout << '\t'<< line << '\n';
                WriteTofile(Filename, ("\n\t\n"+line+ "\n"));
                projects = 1;

                // Explenation 
                /*
                    when expert level comes i is 2, because last time it was 1, 
                    which made it increment once again, it increments because i is 1, which makes is 2.
                    when it's any higher it goes out of the array.

                    Update: I was tired, so i couldnt figure it out. 17/7/2024
                */
            }else{
                //Write to a file function
            WriteTofile(Filename, ("\n" + std::to_string(projects) + (". " + line)));
            projects++;
            total++;
            }
    }
    std::cout << "\nTotal amount of projects is " << total << std::endl;
Datafile.close();

}else{
    std::cout << "File dosen't exist in directory\n"<< std::flush;
 }

 return 0;
}
