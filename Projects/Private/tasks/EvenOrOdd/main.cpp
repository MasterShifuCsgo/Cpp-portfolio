
#include <iostream>
#include <string>
int main()
{

  int number{};

  std::cout << "please enter number: ";
  std::cin >> number;

  std::string condition{};

  if (number % 2 == 0)
  {
    condition = "Even";
  }
  else
  {
    condition = "Odd";
  }

  std::cout << "your number: \"" << number << "\" is " << condition;

  return 0;
}
