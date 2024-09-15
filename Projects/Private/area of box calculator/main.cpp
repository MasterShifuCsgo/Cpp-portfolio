#include <iostream>
#include <string>

float CalcBoxArea(float l, float w, float h)
{

  return 2 * l * w + 2 * l * h + 2 * w * h;
}

int main()
{

  float len{};
  float wid{};
  float hei{};

  std::cout << "please enter box details (length, width, height)\n";

  std::cout << "  length: ";
  std::cin >> len;
  std::cout << "  width: ";
  std::cin >> wid;
  std::cout << "  height: ";
  std::cin >> hei;

  std::cout << "Box area is " << CalcBoxArea(len, wid, hei);

  return 0;
}
