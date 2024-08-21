#ifndef CALCULATOR.H
#define CALCULATOR .H

#include <string>
#include <vector>
/*
    void isEQvalid(std::string eq);

checks for

different operators together like this

any operator = x

xx

++
-*
+*
/*
and more

if () are in valid order

if ) is met first then its invalid
or if ( and ) count isnt x % 2 == 0


log(x65) exept -
log(x65,2) log only has 1 param, pow() doesn't
log()
log(65x2)

log(log(2)) cant calculate multiple functions like so.
*/

class Calculator
{

    // variables

    // methods that clean the equation
    void isOpRowLegal(std::string &eq);
    void isParensLegal(std::string &eq);
    void clear_spaces(std::string &eq);
    void isfuncslegal(std::string &eq);
    void isEQvalid(std::string &eq);
    // return error method
    void error(std::string type, std::string message);
    // number builder
    int buildNum(std::string &eq, size_t &i);
    // func checker
    void areFunctionArgsValid(std::string &eq);

    // methods

public:
    // variables
    const std::vector<std::string> funcs{"log"};

    const std::vector<char> operators{'+', '-', '*', '/', '^'};

    Calculator(std::string &equation)
    {
        // cleans the equation
        clear_spaces(equation);
        isEQvalid(equation);
    }
};

#endif CALCULATOR.H