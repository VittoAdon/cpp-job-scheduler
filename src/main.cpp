#include <iostream>
#include <string>
#include "job.hpp"
#include "job_manager.hpp"
#include "job_execution.hpp"
#include "execute_work.hpp"
#include "job_display.hpp"

int main()
{
    int choice;
    std::string choice_1;
    JobManager manager;
    unsigned long int userId;

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
        {
            std::cout << "Available jobs\n";
            std::cout << "1. CalculateSum\n";
            std::cout << "2. Recreate\n";
            std::cout << "Enter Your Choice: ";
            std::cin >> choice_1;
            std::cout << "\n";
            if (choice_1 == "1")
            {
                manager.createJob("CalculateSum");
                std::cout << "CalculateSum Job Submitted Successfull! \n";
            }
            else if (choice_1 == "2")
            {
                manager.createJob("Recreate");
                std::cout << "Recreate Job Submitted Successfull! \n";
            }
            else
            {
                std::cout << "Invalid job choice!\n";
            }
            std::cout << "\n";
            break;
        }
        case 2:
        {
            execute_work(manager);
            break;
        }
        case 3:
        {
            auto viewJobs = manager.getAllJob();
            if (viewJobs.empty())
            {
                std::cout << "No Job Available!\n";
                std::cout << "\n";
            }
            else
            {
                for (const auto &view : viewJobs)
                {
                    JobDetails(view);
                }
            }
            break;
        }
        case 4:
        {
            std::cout << "Enter User_Id: ";
            std::cin >> userId;
            std::cout << "\n";
            auto jobById = manager.getJobById(userId);
            if (!jobById.has_value())
            {
                std::cout << "Invalid ID or Job not available! \n";
                std::cout << "\n";
            }
            else
            {
                JobDetails(*jobById);
            }
            break;
        }
        case 5:
        {
            std::cout << "Exiting....! \n";
            break;
        }
        default:
        {
            std::cout << "Invalid Choice\n";
            break;
        }
        }
    } while (choice != 5);

    return 0;
}