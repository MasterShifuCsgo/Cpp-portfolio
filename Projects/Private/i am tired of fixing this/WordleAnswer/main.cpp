
#include <iostream>
#include <fstream>
#include <vector>

/*This class is used to guess the wordle word using the latest word and data provided by the user.*/
class Guesser
{
public:
    /*variables*/

    std::string user_word{};
    std::vector<char> user_letters{};
    std::vector<std::string> user_letter_colors{};
    /*constructors*/

    Guesser(std::string last_word_param, std::vector<char> letters_param, std::vector<std::string> letter_colors_param)
        : user_word{last_word_param}, user_letter_colors{letter_colors_param}
    {
        user_letters = letters_param;
    }
    /*setters*/

    /*getters*/

    /*methods*/

    bool has_list_changed(std::vector<std::string> &list_param)
    {

        static std::vector<std::string> list{};

        if (list.size() != list_param.size())
        {
            return true;
        }

        list = list_param;
        return false;
    }

    void guessWord() /*uses logic to guess the wordle word using the letters and color of the letters.*/
    {
        std::fstream wordleAnswers;
        wordleAnswers.open("wordleanswers.txt", std::ios_base::in); /*read input of the file*/

        std::string temp_word;
        std::vector<std::string> possible_words{};
        static std::string blacklisted_letters{};
        if (wordleAnswers.is_open())
        {
            int curr_pos = 0;
            while (std::getline(wordleAnswers, temp_word))
            {

                int curr_pos = 0;

                /*check letter color and do the corresponding logic for it*/

                if (user_letter_colors[curr_pos] == "green")
                {
                    /*logic if the letter is green*/
                    if (temp_word[curr_pos] == user_word[curr_pos])
                    {
                        possible_words.push_back(temp_word);
                    }
                }
                else if (user_letter_colors[curr_pos] == "yellow")
                {
                    /*logic if letter is yellow*/
                    if (temp_word.find(user_word[curr_pos]))
                    {
                        possible_words.push_back(temp_word);
                    }
                }
                else if (user_letter_colors[curr_pos] == "gray" || user_letter_colors[curr_pos] == "grey")
                {
                    blacklisted_letters.push_back(user_word[curr_pos]);
                }

                if (curr_pos <= 5)
                {
                    curr_pos++;
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            std::cerr << "file didnt open. file doesnt exist in directory.\n";
        }

        if (has_list_changed(possible_words))
        {
            guessWord();
        }
        else
        {
            /*list all possible answers and make it pretty*/

            std::cout << "\n+---------------------------------------+n\n|               Answers                 |\n+---------------------------------------+\n"
                      << std::endl;

            for (auto &word : possible_words)
            {
                std::cout << word << '\n';
            }

            std::cout << "\n------------------end------------------\n";
        }
    }
};

bool is_pref_color(std::string color)
{
    if (color == "green")
    {
        return true;
    }
    else if (color == "gray" || color == "grey")
    {
        return true;
    }
    else if (color == "yellow")
    {
        return true;
    }
    return false;
}

void save_word_settings(std::string &last_word, std::vector<std::string> &letter_colors, std::vector<char> &letters)
{

    for (char &letter : last_word)
    {
        letter = tolower(letter); /*makes the last word lowercase*/
        std::string color{};
        std::cout << letter << ": ";
        std::cin >> color;
        if (is_pref_color(color))
        {
            letter_colors.push_back(color);
            letters.push_back(letter);
        }
        else
        {
            std::cout << "\nColor enterd was not available please enter the colors again.\n";
            save_word_settings(last_word, letter_colors, letters);
        }
    }
}

int main()
{

    /*welcomes and asks for the last word the user entered into wordle.*/
    std::string last_word;
    std::vector<char> letters{};
    std::vector<std::string> letter_colors{};

    std::system("cls");
    std::cout << "Welcome to Wordle word guesser!\n";
    std::cout << "enter the last word you entered into wordle: ";
    std::cin >> last_word;
    std::cout << '\n';

    /*saves the color of the letters*/
    std::cout << "was the letter green, yellow or gray:\n";
    save_word_settings(last_word, letter_colors, letters); /*arguments are by reference*/

    /*Word guessing begins here*/

    Guesser Wordle{last_word, letters, letter_colors};
    Wordle.guessWord();

    return 0;
}