#include <iostream>
#include <vector>

int main()
{

    std::vector<char> ops{'+', '-', '*', '/', '^'};

    for (char l : ops)
    {
        int res = static_cast<int>('0' - l);
        std::cout << res << " = " << l << '\n';
    }

    return 0;
}