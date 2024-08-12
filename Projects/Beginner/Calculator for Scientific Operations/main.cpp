#include <iostream>
#include <regex>
#include <string>
#include <vector>

// tempates
//  1. "(\\+\\-\\*/log\\(\\s*(-?\\d+)\\s*,\\s*(-?\\d+)\\s*\\))"

class Calculator
{
    // Member variables

    std::string calculation;

    // regex
    std::vector<std::string> regex_patterns{"(^\\d+(\\+\\-\\*/)\\d+)+$)",
                                            "(\\+\\-\\*/log\\(\\s*(-?\\d+)\\s*,\\s*(-?\\d+)\\s*\\))",
                                            "(\\+\\-\\*/pow\\(\\s*(-?\\d+)\\s*,\\s*(-?\\d+)\\s*\\))"}; // to create more functions use the template above the class.
    std::smatch sm;

public:
    // Constructor
    Calculator(const std::string &user_calculation_param)
        : calculation(user_calculation_param)
    {
    }

    // Method to calculate if the user calculation is valid
    bool isCalculationValid()
    {
        /*take the user calculation, find the default pattern and special patterns if they exist.
         if default pattern doesn't exist return false, else look for special patterns*/
        std::string backup = calculation;
        // find the default pattern.

        for (size_t i{}; i < regex_patterns.size(); i++)
        {

            if (calculation == "")
            {
                return true;
            }
            if (std::regex_search(calculation, sm, std::regex(regex_patterns[i]))) // this loop looks for regex patters defined above.
            {
                // function finds a match; continues to find more matches and if there are no errors and the string is empty, the calcuation is valid.
                // when i changes calculation stays the same, and will hinder the progress to the goal
                calculation = sm.suffix();
            }
            else
            {
                return false;
            }
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
        if (!calculator.isCalculationValid())
        {
            std::cout << "Calculation is not valid." << std::endl;
            exit(0);
        }
        else
        {
        }
    }

    return 0;
}
