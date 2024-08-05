
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
        : user_word{last_word_param}, user_letters{letters_param}, user_letter_colors{letter_colors_param}
    {
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
            size_t i{0};
            while (std::getline(wordleAnswers, temp_word))
            {

                float brackets = i % temp_word.length();

                std::cout << "Iteration: " << i << std::endl;

                if (blacklisted_letters.find(temp_word[brackets]) != std::string::npos)
                {
                    i++;
                }

                /*this part is not important*/
                int i{};
                for (auto &color : user_letter_colors)
                {

                    std::cout << color << "\n count > " << user_letters[i];
                    i++;
                }
                /*^^ this part is not important ^^*/

                //<!--
                /*why is segmentation fault happening?*/
                if (user_letter_colors[brackets] == "green" && user_letters[brackets] == temp_word[brackets])
                { /*if the letter is green and corresponds the same letter as in temp_word, add to the list*/
                    possible_words.push_back(user_word);
                }
                else if (user_letter_colors[brackets] == "yellow" && temp_word.find(user_word[brackets]) != std::string::npos)
                { /* if letter is yellow and can find it in the word, add to the list*/
                    possible_words.push_back(user_word);
                }
                else if (user_letter_colors[brackets] == "gray" || user_letter_colors[brackets] == "grey" && temp_word.find(user_word[brackets]) != std::string::npos)
                { /*if color is gray or grey and letter is in the word, put the letter in the blacklist*/
                    blacklisted_letters.push_back(user_word[brackets]);
                }
                //--!>
                i++;
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

void save_letter_colors(std::string &last_word, std::vector<std::string> &letter_colors)
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
    save_letter_colors(last_word, letter_colors); /*arguments are by reference*/

    /*Word guessing begins here*/

    Guesser Wordle{last_word, letters, letter_colors};
    Wordle.guessWord();

    return 0;
}