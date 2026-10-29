#include <iostream>
#include <string>
#include "job.hpp"
#include "job_manager.hpp"
#include "job_execution.hpp"
#include "execute_work.hpp"

int main()
{
    int choice;
    std::string choice_1;
    JobManager manager;

    do
    {
        std::cout << "1. Submit a job\n";
        std::cout << "2. Process queue\n";
        std::cout << "3. View all jobs\n";
        std::cout << "4. Find job by ID\n";
        std::cout << "5. Exit\n";

        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cout << "\n";

        switch (choice)
        {
        case 1:
            std::cout << "Available jobs\n";
            std::cout << "1. CalculateSum\n";
            std::cout << "2. Recreate\n";
            std::cout << "Enter Your Choice: ";
            std::cin >> choice_1;
            std::cout << "\n";
            if (choice_1 == "1")
            {
                manager.createJob("CalculateSum");
                std::cout << "CalculateSum Creation Successfull! \n";
            }
            else if (choice_1 == "2")
            {
                manager.createJob("Recreate");
                std::cout << "Recreate Creation Successfull! \n";
            }
            else
            {
                std::cout << "Invalid job choice!\n";
            }
            std::cout << "\n";
            break;

        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        default:
            std::cout << "Invalid Choice\n";
            break;
        }
    } while (choice != 5);

    return 0;
}