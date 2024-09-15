
#include <iostream>
#include <string>
#include <stdexcept>

float tempConverter(char convertTo, float amount)
{

  if (convertTo == 'f')
  {
    return (amount - 32) / 1.8;
  }

  return 1.8 * amount + 32;
}

int main()
{

  char type;
  char otherType{};
  float amount{};
  float answer{};
  char uppercaseType{};

  std::cout << "what type would you like to convert? C or F >> ";
  std::cin >> type;

  uppercaseType = type;
  type = tolower(type);
  type == 'c' ? otherType = 'F' : otherType = 'C';

  std::cout << "enter the \"" << uppercaseType << "\" amount >> ";
  std::cin >> amount;

  std::cout << "converting from \"" << uppercaseType << "\" to \"" << otherType << "\"\n";

  if (type == 'c')
  {
    answer = tempConverter('c', amount);
  }
  else if (type == 'f')
  {
    answer = tempConverter('f', amount);
  }
  else
  {
    throw std::invalid_argument("not a valid converable type for this program");
  }

  std::cout << amount << uppercaseType << " is " << answer << otherType;
  return 0;
}
