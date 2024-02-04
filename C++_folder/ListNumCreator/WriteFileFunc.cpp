#include "WriteFileFunc.h"
#include <fstream>
#include <iostream>


std::fstream Writefile;


void WriteTofile(std::string Filename_param, std::string WhatToWrite){

Writefile.open(Filename_param, std::ios::app);

if(Writefile.is_open()){

Writefile << WhatToWrite;

Writefile.close();

}

}
