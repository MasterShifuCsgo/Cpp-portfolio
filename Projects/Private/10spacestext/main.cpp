#include <iostream>
#include <fstream>

int main()
{
    /*holds the amount of arguments number*/
    /*argv[] holds the arguments for int main.*/

    std::fstream file;
    std::fstream writefile;

    file.open("text.txt", std::ios_base::in); /*reading input, in the file*/
    writefile.open("write.txt", std::ios_base::out);
    if (!file.is_open())
    {
        std::cerr << "Error occured: file didnt open, check directory";
    }
    else
    {

        int width{10};

        int last_newline{0};
        std::string line{};
        int space_count{-1};
        std::string temp{};
        while (std::getline(file, line))
        {
            for (size_t j = 0; j < line.size(); j++)
            {
                if (line[j] == ' ')
                {
                    ++space_count;
                    if (space_count == width)
                    {
                        space_count = -1;
                        writefile << line.substr(last_newline, j - last_newline) << '\n'; /*Figure out how i came up with (last_newline, j - last_newline)*/
                        last_newline = j + 1;
                    }
                }
            }
        }
        file.close(); /*close file*/
        writefile.close();
    }

    return 0;
}
