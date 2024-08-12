/*
how to make a regex program
https://cplusplus.com/reference/regex/

Step 1. define your string that has the target sequence.

explain to yourself what is a raw string literal
s-char is a type that can process any letter and escape sequence in the standard library,
wide characters are used to represent (for example) japanese characters. it uses 2 fold the amount of bits to represent characters. wcout to output.
raw string literals are strings that support all the standard library letters but NOT escape sequences.

all of these variables have to have parentheses which are called delimiters, they define the start and end of the raw string.
example. R"(string in here)"

delimiters can not be in the middle of the string.
// R"<<(-_-)>>"; // Error: begin and end delimiters do not match
// R"-()-"-()-"; // Error: )-" appears in the middle and terminates the literal


Step 2. initiate an smatch.

explain to yourself what are match's used for in regex.

std::cmatch	= std::match_results<const char*>
std::smatch	= std::match_results<std::string::const_iterator>
these types should be used accordingly, if you use:
char you use std::cmatch
std::string std::smatch

there are also other matches, look into https://en.cppreference.com/w/cpp/regex/match_results

a mach by default holds no value "", like that.

this type holds character sequences that regural expression matches.
Why is it a specific type, why cant it be a list?
this type is an allocator-aware container, which means it allocates and deallocates memory dynamically as more elements enter or leave the containter,
lists have a predefined size that cant change (you can make it change but this is just easier to use and meant for strings and char types).


Step 3. initiate a regex pattern.
explain to yourself how to initalize a regex pattern.

use accordingly
std::regex = std::basic_regex<char>
std::wregex = std::basic_regex<wchar_t>

https://cplusplus.com/reference/regex/basic_regex/
why is it a type?
std::regex has member types, they are widely used paramaters and return types of member functions.
see link above for more information.

https://cplusplus.com/reference/regex/
To initialize a regex pattern you have to know the basic functions of it.
there are three functions:
regex_search()
regex_replace()
regex_match()

i will be documenting regex_search(1, 2, 3) function
this function returns true if it finds 1 match, regex_match only returns true if the entire sequence matches.

the 1-st parameter is the target string.
the 2-nd parameter is the match parameter, it will be filled by the function of the matching instances.
the 3-rd parameter is the regex pattern. this must be type regex.

for smatch functions theres a website
https://cplusplus.com/reference/regex/match_results/

This program counts the amount of "the" it encounters in the target string.


.suffix() returns the original part of the string after the match .



*/

#include <regex>
#include <iostream>
#include <string>

int main()
{
    system("cls");
    // Step 1.
    std::string log(R"(the quick brown fox jumpes over the lazy dog the the the)");
    // Step 2.
    std::smatch sm;
    // Step 3.
    std::regex pattern("the");

    // regex_search only stores the match once in sm.
    // to count the amount of matches we need to iterate over the search function
    int count{1};
    while (true)
    {

        if (std::regex_search(log, sm, pattern)) // If no match is found sm is an empty string.
        {
            std::cout << "\n#" << count << " Pattern exists: \n  " << '\"' << sm.suffix() << '\"';
            log = sm.suffix(); // replaces log with the original string but cuts off the part left of the latest found match.
        }
        else
        {
            std::cout << " Patterns dont exist";
            break;
        }
        count++;
    }

    std::cout << "\nProgram ended total number of the in the sentance was: " << count - 1;

    return 0;
}
