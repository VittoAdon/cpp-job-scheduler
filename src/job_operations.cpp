#include "job_operations.hpp"
#include <iostream>
#include <fstream>

int CalculateSum(int a, int b)
{
    int c = a + b;
    return c;
}
bool Recreate()
{
    std::ofstream file("job_report.txt");
    if (!file.is_open())
    {
        std::cout << "Failed to Open!\n";
        return false;
    }
    file << "Job has been filed in this report! \n";
    file.close();
    if (!file)
    {
        std::cout << "Failed to Write!\n";
        return false;
    }
    return true;
}