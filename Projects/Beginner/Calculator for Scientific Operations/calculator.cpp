#include <string>
#include <iostream>
#include <cctype>
#include "calculator.h"

void Calculator::error(std::string type, std::string message)
{
    std::cout << "Error occured:\n\t Error type:" << type
              << "\n\tError message:" << message;
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

int Calculator::fParamsNum(std::string &name)
{
}

void Calculator::isfuncslegal(std::string &eq)
{
    /*
log(x65) exept '-'
log(x65,2) log only has 1 param, pow() doesn't
log()
log(65x2)

log(log(2)) cant calculate multiple functions like so.
    */

    // part the looks for the function

    std::string func_name;

    for (size_t i = 0; eq.size(); i++)
    {
        if (isalpha(eq[i]))
        { // found first letter of the function
          // maximum length of a functon is 3

            // save function name
            func_name = eq[i] + eq[i + 1] + eq[i + 2];
            i += 3;

            // check how many params does func take.
            Calculator::fParamsNum(func_name);
        }
    }
}

void Calculator::isEQvalid(std::string &eq)
{
    // all return an error and exit the program if falsy statement is to occur

    // ops legality
    Calculator::isOpRowLegal(eq);

    // the illegal () cases
    Calculator::isParensLegal(eq);

    // illegal function cases
    Calculator::isfuncslegal(eq);
}
