#include <string>
#include <iostream>
#include <cctype>
#include <cmath>
#include "calculator.h"

void Calculator::error(std::string type, std::string message)
{
    std::cout << "Error occured:\n\tError type:    " << type
              << "\n\tError message: " << message;
    exit(1);
}

void Calculator::clear_spaces(std::string &eq)
{
    for (size_t i = 0; i < eq.size(); i++)
    {
        if (eq[i] == ' ')
        {
            eq[i] == '\0';
        }
    }
}

void Calculator::isParensLegal(std::string &eq)
{
    // O(n) time
    // O(1) space

    size_t n = eq.size();

    int balance = 0;

    for (char &lt : eq)
    {
        if (lt == '(')
        {
            balance++;
        }
        else if (lt == ')')
        {
            balance--;
            if (balance < 0)
            {
                Calculator::error("Parentheses", "Parentheses are not correctly used");
            }
        }
    }

    if (balance != 0)
    {
        Calculator::error("Parentheses", "Parentheses are not correctly used");
    }
}

void Calculator::isOpRowLegal(std::string &eq)
{
    // operators xx
    std::vector<char> ops = Calculator::operators;

    // O(n*m), possible optimization to O(n);
    size_t n = eq.size();
    size_t m = ops.size();

    size_t j = 0;
    size_t k = 0;
    char op1;
    char op2;

    for (size_t i = 1; i < n; i++)
    {
        op2 = ops[k];
        k++;
        while (m > j)
        {
            op1 = ops[j];
            if (eq[i - 1] == op1 && eq[i] == op2)
            {
                Calculator::error("operator", "found multiple operators x, xx in row");
            }
            j++;
        }
        j = 0;
    }
}

void Calculator::areFunctionArgsValid(std::string &eq, size_t &i)
{
    /*

    onlt 1 param functions exist.
    log(0.1)
    log(1,2)
    are illegal.

    // check if there are '.' in between parentheses and if more than 1 argument is passed.
    */
    for (i; i < eq.size(); i++)
    {
        if (eq[i] == '.')
        {
            Calculator::error("invalid type", "found a '.' in your equtaion");
        }

        if (eq[i] == ',')
        {
            Calculator::error("invalid type", "found a ',' in your equation");
        }

        if (eq[i] == ')')
        {
            return;
        }
    }
}

int Calculator::buildNum(std::string &eq, size_t &i)
{

    int result = 0;
    bool isminus = false;
    while (eq.size() > i)
    {
        if (eq[i] == '-')
        {
            isminus = true;
            i++;
        }
        else if (isalpha(eq[i]))
        {
            Calculator::error("numbuild", "Found a letter in numbers");
        }

        if (isdigit(eq[i]))
        {
            result = result * 10 + (static_cast<int>(eq[i]) - '0');
        }
        else
        {
            if (isminus)
            {
                result = result * -1;
            }
            return result;
        }

        i++;
    }

    if (isminus)
    {
        result = result * -1;
    }

    return result;
}

void Calculator::isfuncslegal(std::string &eq, size_t &i)
{

    while (eq.size() > i)
        ;
    {
        // part the looks for the function
        if (isalpha(eq[i]) && eq[i + 3] == '(')
        { // found first letter of the function
          // maximum length of a functon is 3
            i += 4;

            // check if there are '.' or ',' in between parentheses and if more than 1 argument is passed.
            Calculator::areFunctionArgsValid(eq, i); // continues as normal if error isnt returned;
            i++;
        }
    }
}

void Calculator::isEQvalid(std::string &eq)
{
    // all exit the program if error occurs.
    for (size_t i = 0; i < eq.size(); i++)
    {

        // ops legality
        Calculator::isOpRowLegal(eq);
        // the illegal () cases
        Calculator::isParensLegal(eq);

        // illegal function cases
        if (isalpha(eq[i]))
        {
            Calculator::isfuncslegal(eq, i);
            std::cout << "func is legal\n"
                      << i << '\n';
        }
    }
}

bool Calculator::doesFuncExist(std::string &name)
{
    const std::vector<std::string> e_name = Calculator::funcs;
    for (size_t i = 0; i < e_name.size(); i++)
    {
        if (e_name[i] == name)
        {
            return true;
        }
    }
    return false;
}

int Calculator::calcResult(std::string &name, int num)
{

    auto fs = Calculator::funcs;

    for (size_t i = 0; i < fs.size(); i++)
    {
        if (name == fs[i])
        {
            switch (i)
            {
            case 0:
                return std::log(num);
                break;
            }
        }
    }

    Calculator::error("calculation", "something went wrong");
    return -1;
}

void Calculator::substitute(std::string &eq, int &fBegin, int &fEnd, int &result)
{
    std::string i_str = std::to_string(result);
    eq.replace(fBegin, fEnd, i_str);
}

void Calculator::ComputeAndSubstituteFunctions(std::string &eq)
{

    std::string func_name;
    // find function

    for (size_t i = 0; i < eq.size(); i++)
    {
        if (isalpha(eq[i]) && eq[i + 3] == '(')
        {
            int fBegin = i;
            func_name = eq[i] + eq[i + 1] + eq[i + 2];
            i += 4;

            bool func = Calculator::doesFuncExist(func_name);

            if (func) // function exists
            {
                int num = Calculator::buildNum(eq, i); // i a reference argument
                int result = Calculator::calcResult(func_name, num);
                int fEnd = i + 1;
                Calculator::substitute(eq, fBegin, fEnd, result); // replaces the function with its result
            }
            else
            {
                Calculator::error("function", "found a function which doesn't exist");
            }
        }
    }
}

double Calculator::arithCalc(std::string &eq)
{
    /*
        "(1+ [2 ) / 3] + 1"
        chooses one to calculate by value of the operators.
        substitutes result to eq.

        repeat
    */

    /*
    when it finds the most valuable operator and tracks the start and end of the calculation (e.g "1/1")
    holds the position if 1 and / 1 <-- number;
    calculates
    then replaces the area with the result.
    */

    /*
    starts the search with the most valuable operator and then goes down to the lowest ranking op
    looks for this operator in the function. if it finds it, it bulds the numbers left and right side.
    */

    std::vector<char> ops = Calculator::operators;

    signed int right_num{};
    signed int left_num{};
    signed int num{};

    int i = ops.size() - 1;

    bool side = true;

    std::vector<char>::iterator it = ops.end();

    for (size_t j = 0; j < eq.size(); j++)
    { // counts ops
        for (; it != ops.begin(); --it)
        { // counts letters in eq
            std::cout << "loop" << '\n';
            if (eq[j] == *it)
            {
                // build numbers left and right from the operator.
                int j_save = j;
                // build right and left side number.
                while (isdigit(eq[j]))
                {
                    num = num * 10 + static_cast<int>(eq[j] - '0');
                    ++j;
                }

                j = j_save;

                right_num = num;
                std::cout << "right_num: " << right_num << '\n';

                while (isdigit(eq[j]))
                {
                    num = num * 10 + static_cast<int>(eq[j] - '0');
                    --j;
                }
                std::cout << "left_num: " << right_num << '\n';

                double result{};
                std::cout << "*it: " << *it << '\n';

                /*
                    std::vector<char> ops{'+', '-', '*', '/', '^'};

                    for (char l : ops)
                    {
                        int res = static_cast<int>('0' - l);
                        std::cout << res << " = " << l << '\n';
                    }

                    //you enter your operators in the list, and run the file.
                    //you can see their corresponding number.
                */

                switch (static_cast<int>('0' - *it))
                {
                case 5:
                    result = left_num + right_num;
                    break;
                case 3:
                    result = left_num - right_num;
                    break;
                case 6:
                    result = left_num * right_num;
                    break;
                case 1:
                    result = left_num / right_num;
                    break;
                case -46:
                    result = std::pow(left_num, right_num);
                    break;
                }
            }
        }
    }
}

int Calculator::calculate(std::string &eq)
{

    // calculate the functions and replace the function with the result
    Calculator::ComputeAndSubstituteFunctions(eq);

    // algo that calculate 1+1 ... and more together into a result

    int result = Calculator::arithCalc(eq);
    return result;
}
