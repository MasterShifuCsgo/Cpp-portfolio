#include <iostream>
#include <cstring>
#include <sstream>

std::string Smaller_or_bigger(unsigned int computer_num, unsigned int user_number)
{

    if (computer_num > user_number)
    {
        return "Bigger";
    }
    return "Smaller";
}

int main()
{

    std::system("cls"); /*clear out the console for the user*/

    /*Welcome to user*/

    std::cout << "Welcome to this Number Guessing game!\n";

    /* rules for the game */
    std::cout << "To play the game you must choose a range form 0 - (specified range. intiger type).\n";
    std::cout << "specified range + 1 to quit\n";
    unsigned int user_range{};
    while (true)
    {

        std::cout << "Please specify the range >> ";
        std::cin >> user_range;

        if (std::cin.fail()) // check if cin failed. (letter is put into an integral type)
        {
            std::system("cls");
            std::cout << "Please enter a valid value that does not deduce to 0. letters deduce to 0.\n";
            std::cin.clear();  // clears the error messages and allows it to work like normal.
            std::cin.ignore(); // clears the last input. clears the input buffer.
            continue;
        }

        /*tell the user what the computer is doing*/
        std::stringstream ss;
        ss << "Computer is choosing random number from range 0 - {}\n", user_range;
        std::cout << ss.str() << std::endl;
        ss.str(""); /*clear the ss var*/

        /*computer chooses random number from the specified range*/
        time_t current_time = time(NULL); // seed is the current time.
        srand(current_time);
        unsigned int random_num = rand() % user_range; // creates random number for the computer to use. 0 - user_range

        std::system("cls"); // sets up the guessing part for the user, clears the terminal

        /*User guessing part*/
      
        unsigned int user_guess_num{};
        unsigned int user_guess_amount{};
        std::cout << "Begin Guessing the random number\n\n";

        while (true) // breaks if the user guesses the right number
        {

            /*user guessing random number the computer chose*/

            std::cout << "Game Data:\n";
            std::cout << "\tTries: " << user_guess_amount << std::endl;
            std::cout << "\tLast Number Guessed: " << user_guess_num << std::endl;

            std::cout << "\nGuess range 0 - " << user_range;
            std::cout << "\n\nComputers number is \"" << Smaller_or_bigger(random_num, user_guess_num) << "\" than the Your number " << user_guess_num << std::endl;
            std::cout << "I think it's number ";
            std::cin >> user_guess_num;

            if (random_num == user_guess_num)
            { /*if the user num and computer number are the same Congradulate the user.*/
                std::system("cls");
                break;
                /*congradulates the user for guessing the number*/
            }
            else if (user_guess_num == (user_range + 1))
            { /*user wants to quit*/

                std::cout << "\nCom. num >> " << random_num;
                std::cout << "\n\n\tGoodbye" << std::endl;
                return 0;
            }
            std::system("cls");
            user_guess_amount += 1;
        }
        /*User Guessed the number*/

        std::cout << "\n\nCongratulations You guessed the number!! \n\n\t Com. " << random_num << " == " << user_guess_num << " You.\n"
                  << std::endl;

        std::cout << "Tries: " << user_guess_amount << std::endl;
        std::cout << "Guess range 0 - " << user_range;

        /*Ask if the user wants to play again*/
        std::cout << "\n\nDo you want to play again?\n\nType \"Y\" if YES and any letter to quit";
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
            std::cout << "\n\n\tGoodbye" << std::endl;
            return 0;
        }
    }
    return 0;
}
