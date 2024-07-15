
#include <iostream>
#include <cstring>
#include <sstream>

std::string Num_to_element(int number)
{

    if (number == 1)
    {
        return "Rock";
    }
    else if (number == 2)
    {
        return "Paper";
    }
    else
    {
        return "Scissors";
    }

    std::stringstream ss;
    ss << "Value does not correspond to game element" << number;
    return ss.str();
}

int main()
{
    std::system("cls"); // clean interface for playing
    bool Repeat_game = true;

    while (Repeat_game)
    {
        /* Game */
        /*Rock paper scissors*/

        // ask the user rock, paper or scissors.

        int user_option{};
        std::cout << "Enter a number of your game Element 1-3";
        std::cout << "\n Rock: 1\n Paper: 2 \n Scissors: 3 \n Number ";

        std::cin >> user_option;
        std::cout << "\n\nComputer Thinking...";
        std::system("cls"); // clears the asking part and shows the results

        /*Computer picks a random number form 1-3*/

        /*uses the time as a seed for rand num gen*/
        time_t current_time = time(NULL);
        srand(current_time);
        int random_num = 1 + (rand() % 3); /*numbers from 1-3*/

        /*Game logic starts here*/
        std::cout << "Result: \n";

        std::cout << "Com. " << Num_to_element(random_num) << " vs. " << Num_to_element(user_option) << " Hum.\n";

        if (user_option == random_num)
        {
            std::cout << "TIE!";
        }
        else if (user_option > random_num && user_option != 1 && random_num != 1)
        {
            std::cout << "Winner!";
        }
        else
        {
            std::cout << "Loser!";
        }

        /*Game logic ends here*/

        /*Ask if the user wants to play again*/
        std::cout
            << "\n\nDo you want to play again?\n Type \"Y\" if YES and \"N\" if NO: ";
        std::string user_agreement{};
        std::cin >> user_agreement;
        // logic for checking
        if (user_agreement == std::string("Y") || user_agreement == std::string("y"))
        {
            std::cout << "Continuing Game...\n";

            std::system("cls");
        }
        else
        {
            Repeat_game = false;
        }
    }

    std::system("cls"); // just making it prettier
    std::cout << "\n\nThank you for playing my game!!\n\n"
              << std::endl;

    return 0;
}
