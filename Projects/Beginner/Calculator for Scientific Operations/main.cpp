#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <clocale>
#include <math.h>

class Display
{
    /*private variables*/

    std::stringstream formatted_display;
    /*numbers that the user has inputed*/
    /*variables that will be used to make calculations and make the formatted string*/

    /*double *user_numbers = new double();
    std::string *user_operations = new std::string;*/

    std::vector<double> user_numbers{};
    std::vector<char> user_operations{};
    std::string G_user_calculation{};
    /*Private Methods*/

    void Update_number_display() /*updates the fancy numbers in a row part*/
    {

        std::string s = G_user_calculation;

        s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());

        formatted_display << s << '\n';
        std::cout << formatted_display.str();
        formatted_display.str("");
    }

    void clear_user_based_variables()
    {
        user_numbers.clear();
        user_operations.clear();
    }

    std::string available_operations{"+-*/^%"};
    double calculator(double &a, double &b, const char &method)
    {

        int use_method = available_operations.find(method);

        switch (use_method)
        {
        case 0:
            return a + b;
        case 1:
            return a - b;
        case 2:
            return a * b;
        case 3:
            return a / b;
        case 4:
            return std::pow(a, b);
        case 5:
            std::cout << "Modulo not available in this calculator\n";
            break;
        }

        return 0;
    }

    void Clear_numRow()
    {
        formatted_display.str("Terminal Cleared\n\n");
        std::cout << formatted_display.str();
        formatted_display.str("");
    }

    const char *make_lowercase(const std::string &tolowercase)
    {

        char *lowercase_char{};

        for (size_t i = 0; i < tolowercase.size(); i++)
        {
            lowercase_char += std::tolower(tolowercase[i]);
        }
        return lowercase_char;
    }

    bool is_computable(std::string &user_calc)
    {

        for (size_t i = 1; i < user_calc.size(); i++)
        {

            bool forward = available_operations.find(user_calc[i]) != std::string::npos;    /*true = found operator*/
            bool behind = available_operations.find(user_calc[i - 1]) != std::string::npos; /*false = didnt find operator*/

            if (forward && behind)
            {
                return false;
            }
        }
        return true;
    }

    void ask_user_calc()
    {
        std::string user_calculation;
        std::cout << "Your calculation is not computable or an error occured. Please try again. \n >> ";
        std::getline(std::cin, user_calculation);

        G_user_calculation = user_calculation;
    }

public:
    /*constructors*/

    /*public variables*/

    /*Setters*/

    void Set_G_variables(std::string &user_calculation) /*sholdnt look like this, parameter should be a list. and the logic goes form there*/
    {
        G_user_calculation = user_calculation;
    }

    /*methods*/

    void Filter_calculation_and_store()
    {

        size_t number{0};

        bool is_user_calc_clean = is_computable(G_user_calculation);

        if (is_user_calc_clean)
        {

            /*Find all the operators present and add them to the list.*/
            for (size_t i = 0; i < G_user_calculation.size(); i++)
            {
                if (std::isspace(G_user_calculation[i]))
                {
                    i++;
                }

                if (available_operations.find(G_user_calculation[i]) != std::string::npos)
                {
                    user_operations.push_back(G_user_calculation[i]);
                }
                else
                {
                    /*when there are numbers like this 33 it adds them to the array like this 3, 3, fix this*/

                    if (number + 1 == i)
                    {
                        /*user_numbers.size() - 1 is the last element that was added*/

                        int last_element = user_numbers.size() - 1;

                        user_numbers.at(last_element) = user_numbers.at(last_element) * 10 + G_user_calculation[i] - '0';
                        std::cout << "user_numbers.at(" << last_element << ") is " << user_numbers.at(last_element) << std::endl;
                    }

                    user_numbers.push_back(G_user_calculation[i] - '0');

                    number = i;
                }
            }
        }
        else
        {
            ask_user_calc();
            Filter_calculation_and_store();
        }
    }

    void Update()
    {

        const char *user_calc_char = make_lowercase(G_user_calculation);

        if (user_calc_char == "clear")
        {

            Clear_numRow();
            return;
        }

        Update_number_display();
    }

    void Calculate()
    {

        std::vector<double> answer{};

        for (size_t i = 1; i < user_numbers.size(); i++)
        {
            /*check user_calculations value  right side from [i] to see if there are any numbers*/
            /* double calculator(double &a, double &b, const char &method) */

            answer.push_back(calculator(user_numbers[i - 1], user_numbers[i], user_operations[i - 1]));
        }

        std::cout << "Answer >> " << answer[answer.size() - 1] << std::endl;

        clear_user_based_variables();
    }
};

int main()
{

    /*ask the user for numbers and operations to do.*/

    std::string user_calculation{};
    Display user_input;
    while (true)
    {

        std::cout << "Calculator for Scientific Operations\n\n\t";
        std::cout << "Hello user, please enter your calculation (e.g 1+2 or 3*4/5)\n >> ";
        std::getline(std::cin, user_calculation);

        user_input.Set_G_variables(user_calculation);

        user_input.Filter_calculation_and_store();
        user_input.Update();
        user_input.Calculate();
    }

    return 0;
}
