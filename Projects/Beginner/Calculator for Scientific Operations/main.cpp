#include <iostream>
#include <string>
#include <vector>
#include "calculator.h"

int main()
{

    std::cout << "Welcome to Scientific Calculator\n";

    while (true)
    {
        std::string equation;
        std::cout << "\n------ScCalc------\n";
        std::cout << "Enter your calculation >> ";
        std::getline(std::cin, equation);

        Calculator calc(equation); // clenses the equation of unwanted things
    }

    return 0;
}
