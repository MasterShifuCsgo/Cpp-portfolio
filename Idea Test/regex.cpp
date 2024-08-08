#include <iostream>
#include <regex>
#include <string.h>
using namespace std;

int main()
{
    // string to be searched
    string mystr = "She sells_sea shells in the sea shore";

    // regex expression for pattern to be searched
    regex regexp("s[a-z_]+");

    // flag type for determining the matching behavior (in this case on string objects)
    smatch m;

    // regex_search that searches pattern regexp in the string mystr
    regex_search(mystr, m, regexp);

    cout << "String that matches the pattern:" << endl;
    for (auto x : m)
        cout << x << " ";
    return 0;
}

// regex_search example
#include <iostream>
#include <string>
#include <regex>

int main()
{
    std::string s("this subject has a submarine as a subsequence");
    std::smatch m;
    std::regex e("\\b(sub)([^ ]*)"); // matches words beginning by "sub"

    std::cout << "Target sequence: " << s << std::endl;
    std::cout << "Regular expression: /\\b(sub)([^ ]*)/" << std::endl;
    std::cout << "The following matches and submatches were found:" << std::endl;

    while (std::regex_search(s, m, e))
    {
        for (auto x : m)
            std::cout << x << " ";
        std::cout << std::endl;
        s = m.suffix().str();
    }

    return 0;
}