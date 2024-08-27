double Calculator::arithCalc(std::string &eq)
{
    /*
        "(1+ [2 ) / 3] + 1"
        chooses one to calculate by value of the operators.
        substitutes result to eq.

        repeat
    */

    /*
    when it finds the most valuable operator and tracks the start and end of the calculation (e.g "1/1")
    holds the position if 1 and / 1 <-- number;
    calculates
    then replaces the area with the result.
    */

    /*
    starts the search with the most valuable operator and then goes down to the lowest ranking op
    looks for this operator in the function. if it finds it, it bulds the numbers left and right side.
    */

    std::vector<char> ops = Calculator::operators;

    signed int right_num{};
    signed int left_num{};
    signed int num{};

    int i = ops.size() - 1;

    bool side = true;

    std::vector<char>::iterator it = ops.end() - 1;

    for (; it != ops.begin() - 1; --it)
    { // counts ops
        for (size_t j = 0; j < eq.size(); j++)
        { // counts letters in eq
            std::cout << "eq[j]: " << eq[j] << '\n';
            if (eq[j] == *it)
            {
                std::cout << "if" << '\n';
                // build numbers left and right from the operator.
                int j_save = j;
                // build right and left side number.
                while (isdigit(eq[j]))
                {
                    std::cout << "left" << '\n';
                    num = num * 10 + static_cast<int>(eq[j] - '0');
                    ++j;
                }

                j = j_save;

                right_num = num;
                std::cout << "right_num: " << right_num << '\n';

                while (isdigit(eq[j]))
                {
                    std::cout << "left" << '\n';
                    num = num * 10 + static_cast<int>(eq[j] - '0');
                    --j;
                }
                std::cout << "left_num: " << right_num << '\n';

                double result{};
                std::cout << "*it: " << *it << '\n';

                /*
                    std::vector<char> ops{'+', '-', '*', '/', '^'};

                    for (char l : ops)
                    {
                        int res = static_cast<int>('0' - l);
                        std::cout << res << " = " << l << '\n';
                    }

                    //you enter your operators in the list, and run the file.
                    //you can see their corresponding number.
                */

                switch (static_cast<int>('0' - *it))
                {
                case 5:
                    result = left_num + right_num;
                    break;
                case 3:
                    result = left_num - right_num;
                    break;
                case 6:
                    result = left_num * right_num;
                    break;
                case 1:
                    result = left_num / right_num;
                    break;
                case -46:
                    result = std::pow(left_num, right_num);
                    break;
                }
            }
        }
    }
}