#include <iostream>
#include <limits>

/*Conclusion*/

/*When modulo operator is used the maximum number that could be used is n - 1, where n is word_length. 0 to n-1*/

int main()
{

    int word_length = 5;

    int infinity = std::numeric_limits<int>::max();

    for (size_t i = 1; i < infinity; i++)
    {
        int temp_num = i % word_length;

        std::cout << "iteration: " << i << " | i % word_length++ == " << temp_num << '\n';

        if (i > 50)
        {
            return 0;
        }
    }

    return 0;
}
