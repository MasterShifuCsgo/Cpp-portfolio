#include <iostream>
#include <vector>

int calc_CGPA(std::vector<int> grade_points);

int main()
{

    std::vector<int> grade_points{
        8,
        9,
        7,
        6,
        7,
        8};

    // grade_points = {5, 6, 7, 8, 9, 10, 11, 5, 6, 7, 8, 9, 6, 8, 6, 5, 7, 7, 6, 9, 0, 6, 7, 9, 11, 7, 6, 5, 0, 8, 6, 5, 111};

    int CGPA = calc_CGPA(grade_points);

    std::cout << "Total CGPA is >> " << CGPA << std::endl;

    return 0;
}

int calc_CGPA(std::vector<int> grade_points)
{
    int subject_amount = grade_points.capacity();

    int total_GP{0};
    for (int i{1}; i < subject_amount; i++)
    {
        total_GP += grade_points.at(i);
    }

    return total_GP / subject_amount;
}
