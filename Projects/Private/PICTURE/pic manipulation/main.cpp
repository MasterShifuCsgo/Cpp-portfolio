#include <fstream>
#include <cmath>
#include <iostream>
int main()
{

  std::ofstream image;
  image.open("image.ppm");

  int HEIGHT{255};
  int WIDTH{255};
  int MAX_COLORS{256};

  if (image.is_open())
  {

    image << "P3" << std::endl; // enable rgb
    image << HEIGHT << ' ' << WIDTH << std::endl;
    image << MAX_COLORS << std::endl;

    int equation{};
    int equation2{};
    int equation3{};

    int xs = 0;

    bool start = true;
    for (size_t y{}; y <= HEIGHT; ++y)
    {
      for (size_t x{}; x <= WIDTH; ++x)
      {
        xs = x;
        switch (y % 3)
        {
        case 0:

          equation = x;
          equation2 = 0;
          equation3 = 0;
          break;
        case 1:
          equation = 00;
          equation2 = x;
          equation3 = 0;
          break;
        case 2:
          equation = 0;
          equation2 = 0;
          equation3 = x;
          break;
        }
        image << (equation) % MAX_COLORS << ' ' << (equation2) % MAX_COLORS << ' ' << (equation3) % MAX_COLORS << std::endl;
      }
    }
  }
  return 0;
}
