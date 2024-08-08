#include <iostream>
#include <regex>
#include <string>

class Calculator
{
    // Member variables
    std::string calculation;
    std::string regex_pattern{"(log\\(\\s*(-?\\d+)\\s*,\\s*(-?\\d+)\\s*\\))"};
    std::regex reg; // staic member initialization.
    std::smatch matches;

public:
    // Constructor
    Calculator(const std::string &user_calculation_param)
        : calculation(user_calculation_param),
          reg(regex_pattern) // Initialize regex object
    {
    }

    // Method to calculate if the user calculation is valid
    bool isCalculationValid()
    {
        // Use std::regex_search to check if the calculation matches the pattern
        if (std::regex_search(calculation, matches, reg))
        {
            // saves all matches to matches smatch variable
            return true;
        }
        else
        {
            std::cout << "No match!" << std::endl;
            return false;
        }
    }
};

int main()
{
    // Welcome user
    std::cout << "Hello User Welcome to \"Calculator for Scientific Operations\" program." << std::endl;

    // Main loop for the calculator
    while (true)
    {
        std::cout << "\n-------Calculator-------\n\n";

        // Grab the string of the user calculation
        std::string user_calculation;
        std::cout << "Please enter your calculation:\n   >> ";
        std::getline(std::cin, user_calculation);

        // Create a Calculator object with the user input
        Calculator calculator(user_calculation);

        // Check if the calculation is valid
        if (calculator.isCalculationValid())
        {
            std::cout << "Calculation is valid." << std::endl;
        }
        else
        {
            std::cout << "Calculation is not valid." << std::endl;
            return 0;
        }
    }

    return 0;
}
