/*
There's a medical treatment that is only applicable if your age is between 21 and 39 inclusive
(21 and 39 are included in the range) .
Your task as a C++ developer is to write a program that checks whether the user is eligible for the treatment.
*/

#include <iostream>

void boo(int age)
{

  bool step{false};

  if (age > 39)
  {
    step = true;
    std::cout << "too old!";
  }

  if (age < 21)
  {
    step = true;
    std::cout << "too young!";
  }

  if (!step)
  {
    std::cout << "you're in!";
  }
}

int main()
{

  unsigned int age{};
  std::cout << "enter your age: ";
  std::cin >> age;

  boo(age);
  return 0;
}
