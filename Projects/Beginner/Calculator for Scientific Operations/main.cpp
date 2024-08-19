#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <iomanip>
#include <cmath>
#include <sstream>
/*

        for (auto name : available_funcs) {
        for (char letter : name) {
            func_id += static_cast<int>(letter); // Add ASCII values of each character
        }
        std::cout << name<< ": " << func_id << std::endl;
*/

class Calculator
{

    // variables

    // methods

    // password / id creators
    int create_func_id(std::string &func_name)
    {
        int func_id = 0;

        for (char &letter : func_name)
        {
            func_id = func_id * 10 + static_cast<int>(letter - '0'); // aab and baa are not the same
        }

        return func_id;
    }

    // error mothods
    void return_error(std::string error_type, std::string error_message) // error message could be string stream object
    {
        float er_len = error_message.size();
        if (er_len == 3 || er_len == 5 || er_len == 7 || er_len == 9)
        {
            er_len = er_len - 1;
        }
        std::setfill('-');
        std::cout << "error occured: \n  error_type: " << error_type << "\n  error message: " << error_message << '\n';
        std::cout << std::internal << std::setw(er_len) << "PROGRAM-END" << std::setw(er_len);

        exit(0);
    }

    // format the equation

    bool doesFuncExist(std::string func_name)
    {
        std::vector<std::string> VALIDFUNCNAMES{"log", "pow"}; // should be a set

        // O(i)
        bool func_exist = false;
        for (size_t i = 0; i < VALIDFUNCNAMES.size(); i++)
        {
            if (VALIDFUNCNAMES[i] == func_name)
            {
                func_exist = true;
                break;
            }
        }

        if (!func_exist)
        {
            return_error("Invalid function", "Your function doesnt exist");
        }

        return func_exist;
    }

    void remove_spaces(std::string &eq)
    {

        for (size_t i = 0; i < eq.size(); i++)
        {
            if (isspace(eq[i]))
            {
                eq[i] = '\0'; // equal to nothing
            }
        }
    }

    // function that look for faults, such as ++ of any cmbination of operators

    void checkIfCalculatable(std::string &eq)
    {
        doesFuncExist(eq);
    }

    void format_func(std::string &eq)
    {
        remove_spaces(eq);
        checkIfCalculatable(eq);
    }

    // special functions

    std::vector<int> build_num(std::string eq, int pos) // problem specific function
    {

        std::vector<int> details{};
        int num{};

        if (eq[pos] == '-')
        { // check if num is negative
            pos++;
            num = num * -1;
        }

        while (isdigit(eq[pos]))
        {
            num = num * 10 + (int)(eq[pos] - '0'); // moves num the the right and then appends the number "+ number";
            pos++;
        }
        pos--;

        details.push_back(num);
        details.push_back(pos);
        return details; // return built number
    }

    // calculating functions

    int calculate_function(std::string &func_name, std::vector<int> func_nums)
    {
        // check function name.

        // O(i)
        bool func_exist = doesFuncExist(func_name);

        // if func_name is valid; calculation function:

        int result = 0;
        // create func id for swtich statement
        /// a function that takes the function name and sees if the vector has a corresponding length to it. to be made
        switch (create_func_id(func_name))
        {
        case 6685: // log()

            result = std::log(func_nums[0]);
            break;
        case 7101: // pow()
            result = std::pow(func_nums[0], func_nums[1]);
            break;
        default:
            return_error("func(x,y)", "Something went wrong calculating a function");
        }
        return result;
    }

public:
    // constructors

    Calculator(std::string &eq_param)
    {
        format_func(eq_param); // removes all the spaces
    }

    // variables

    // methods

    // 1. searches for log functions and calculages them

    void processAndReplaceMathFunctions(std::string &eq)
    {

        std::string func_name;
        std::vector<int> func_contents;

        std::vector<int> details{};
        for (size_t i = 0; i < eq.size(); i++)
        {
            if (isalpha(eq[i]) && eq[i + 3] == '(') // max length of a function can only be 3 letters, log(x,y), pow(x,y);
            {
                int start_of_func = i;

                func_name = eq[i] + eq[i + 1] + eq[i + 2];
                i += 4; // position is now (1 <-- (the number) in the string.

                // number builder
                details = build_num(eq, i);
                i = details[1];                      // updates iterator now ,1 <-- number
                func_contents.push_back(details[0]); // pushes built number

                details = build_num(eq, i);
                i = details[1];                      // updates iterator
                func_contents.push_back(details[0]); // pushes built number

                int result = calculate_function(func_name, func_contents);
                // repace the functions location with result.

                // get the length of numers

                eq.replace(start_of_func - 1, i, std::to_string(result)); // example: log(x,y) --> result (calculated num)
            }
        }
    }
};

void say_tutorial()
{

    std::cout << "Tutorial\n";
    std::cout << "1. Function names are 3 letters, and must be written like so: log(1,2), only numbers are supported\n";
}

int main()
{
    std::cout << "Welcome to Scientific Calculator";
    say_tutorial();
    std::cout << "\n--------Scientific-Calculator--------\n";
    std::string equation;
    std::cout << "\nPlease enter you calculation >> ";
    std::getline(std::cin, equation);

    Calculator calc(equation); // used to clear the equation of bad things ' ' ,
    calc.processAndReplaceMathFunctions(equation);

    return 0;
}
