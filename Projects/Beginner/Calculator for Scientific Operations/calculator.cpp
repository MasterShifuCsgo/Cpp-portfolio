#include <string>
#include <iostream>
#include <cctype>
#include <cmath>
#include <typeinfo>
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

  int op_it{};

  for (size_t i{}; i < eq.size(); ++i)
  {
    if (ispunct(eq[i]) && eq[i] == '^')
    {
      op_it++;
    }
    else
    {
      op_it = 0;
    }

    if (op_it >= 2)
    {
      Calculator::error("operator", "multiple operators found in a row");
    }
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

/// @brief
/// @param eq
int Calculator::arithCalc(std::string &eq)
{
  std::vector<char> ops = Calculator::operators;

  signed long long int right_num{};
  signed long long int left_num{};
  signed long long int num{};

  std::string Snum{};

  //  Iterate through the operators from highest precedence to lowest
  for (auto it = ops.rbegin(); it != ops.rend(); ++it)
  {
    for (size_t j = 0; j < eq.size(); ++j)
    {
      if (eq[j] == *it)
      {

        // Reset num for each side
        num = 0;

        // Parse right-hand number
        size_t pos = j + 1;
        while (pos < eq.size() && isdigit(eq[pos]))
        {
          num = num * 10 + (eq[pos] - '0');
          ++pos;
        }
        Calculator::end_eq = pos;
        right_num = num;
        num = 0; // Reset num
        // Parse left-hand number
        pos = j - 1;
        while (pos < eq.size() && isdigit(eq[pos]))
        {
          Snum = Snum + std::to_string((eq[pos] - '0'));
          --pos;
        }
        Calculator::start_eq = pos + 1;
        for (size_t i = Snum.size() - 1; i != -1; --i)
        {
          num = num * 10 + static_cast<double>(Snum[i] - '0');
        }
        left_num = num;

        // Perform the operation
        int result = 0;
        switch (*it)
        {
        case '+':
          result = left_num + right_num;
          break;
        case '-':
          result = left_num - right_num;
          break;
        case '*':
          result = left_num * right_num;
          break;
        case '/':
          if (right_num != 0)
            result = left_num / right_num;
          else
            std::cerr << "Division by zero error\n";
          break;
        case '^':
          result = std::pow(left_num, right_num);
          break;
        }

        // Substitute result back into eq if needed (this part would depend on how you manage eq)
        // For example, replacing "left_num op right_num" with the result

        // replace the found equation (e.g 1+1) with the result
        // start or end go out of range.

        return result;
      }
    }
  }
}

bool Calculator::isOnlyNum(std::string &eq)
{

  for (size_t i = 0; i < eq.size(); i++)
  {
    if (ispunct(eq[i]) || eq[i] == '^')
    {
      return false;
    }
  }

  return true;
}

int Calculator::calculate(std::string &eq)
{
  // calculate the functions and replace the function with the result
  Calculator::ComputeAndSubstituteFunctions(eq);
  // algo that calculate 1+1 ... and more together into a result

  int res{};
  int s{};
  int e{};

  bool steps = true;
  while (!isOnlyNum(eq))
  {
    res = Calculator::arithCalc(eq);
    s = Calculator::start_eq;
    e = Calculator::end_eq;
    eq.replace(s, e, std::to_string(res));
    if (steps)
    {
      std::cout << "eq: " << eq << '\n';
    }
  }

  std::cout << "res: " << res << std::endl;

  return 0;
}
