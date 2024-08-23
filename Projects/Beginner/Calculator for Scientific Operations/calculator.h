#include <string>
#include <vector>

class Calculator
{

    // variables

    // methods that clean the equation
    void isOpRowLegal(std::string &eq);
    void isParensLegal(std::string &eq);
    void clear_spaces(std::string &eq);
    void isfuncslegal(std::string &eq, size_t &i);
    void isEQvalid(std::string &eq);
    // return error method
    void error(std::string type, std::string message);
    // number builder
    int buildNum(std::string &eq, size_t &i);
    // func checker
    void areFunctionArgsValid(std::string &eq, size_t &i);

    // calculate methods
    bool doesFuncExist(std::string &name);
    void ComputeAndSubstituteFunctions(std::string &eq);
    int calcResult(std::string &name, int num);
    void substitute(std::string &eq, int &fBegin, int &fEnd, int &resultt);
    double arithCalc(std::string &eq);

public:
    // variables
    /*to add more functions,
    add function to func list, and implement the feture to calcResult*/
    const std::vector<std::string> funcs{"log"};
    const std::vector<char> operators{'+', '-', '*', '/', '^'};

    Calculator(std::string &equation)
    {
        // cleans the equation
        clear_spaces(equation);
        isEQvalid(equation);
    }

    // methods

    int calculate(std::string &eq);
};
