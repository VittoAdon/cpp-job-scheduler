#include <iostream>
#include <string>
#include <stdexcept>

#include "job.hpp"
#include "job_manager.hpp"
#include "job_execution.hpp"
#include "execute_work.hpp"
#include "job_display.hpp"
#include "job_execution_record_manager.hpp"

int main()
{
    int choice = 0;

    JobManager manager;
    JobExecutionRecordManager jobExection_Manager;

    jobExection_Manager.create_Record(10, 1);
    jobExection_Manager.create_Record(10, 2);
    jobExection_Manager.create_Record(20, 1);
    auto record_history = jobExection_Manager.getHistory_ById(10);
    for (const auto &record : record_history)
    {
        std::cout << record.Execution_Id << "\n";
        std::cout << record.Job_Id << "\n";
        std::cout << record.Attempt_Number << "\n";
    }

    // do
    // {
    //     std::string input;
    //     std::size_t pos;

    //     std::cout << "1. Submit a job\n";
    //     std::cout << "2. Process queue\n";
    //     std::cout << "3. View all jobs\n";
    //     std::cout << "4. Find job by ID\n";
    //     std::cout << "5. Exit\n";
    //     std::cout << "Enter your choice: ";
    //     std::getline(std::cin, input);

    //     std::cout << "\n";

    //     try
    //     {
    //         choice = std::stoi(input, &pos);
    //         if (pos != input.length())
    //         {
    //             throw std::invalid_argument("Invalid Input, Please Enter The Number! \n");
    //         }

    //         switch (choice)
    //         {
    //         case 1:
    //         {
    //             std::string input_1;
    //             std::size_t pos_1;

    //             std::cout << "Available jobs\n";
    //             std::cout << "1. CalculateSum\n";
    //             std::cout << "2. Recreate\n";
    //             std::cout << "Enter Your Choice: ";
    //             std::getline(std::cin, input_1);
    //             std::cout << "\n";

    //             try
    //             {
    //                 int choice_1 = std::stoi(input_1, &pos_1);
    //                 if (pos_1 != input_1.length())
    //                 {
    //                     throw std::invalid_argument("Invalid Input, Please Enter the Number. \n");
    //                 }

    //                 if (choice_1 == 1)
    //                 {
    //                     manager.createJob(JobType::CalculateSum);
    //                     std::cout << "CalculateSum Job Submitted Successfull! \n";
    //                 }
    //                 else if (choice_1 == 2)
    //                 {
    //                     manager.createJob(JobType::RecreateFile);
    //                     std::cout << "Recreate Job Submitted Successfull! \n";
    //                 }
    //                 else
    //                 {
    //                     std::cout << "Invalid job choice!\n";
    //                 }
    //                 std::cout << "\n";
    //             }
    //             catch (const std::invalid_argument &)
    //             {
    //                 std::cout << "Error: Invalid Input. Please enter a valid number. \n";
    //             }
    //             catch (const std::out_of_range &)
    //             {
    //                 std::cout << "Error: Input value is too large \n";
    //             }
    //             break;
    //         }

    //         case 2:
    //         {
    //             execute_work(manager);
    //             break;
    //         }

    //         case 3:
    //         {
    //             auto viewJobs = manager.getAllJob();
    //             if (viewJobs.empty())
    //             {
    //                 std::cout << "No Job Available!\n";
    //                 std::cout << "\n";
    //             }
    //             else
    //             {
    //                 for (const auto &view : viewJobs)
    //                 {
    //                     JobDetails(view);
    //                 }
    //             }
    //             break;
    //         }

    //         case 4:
    //         {
    //             std::string userId_Input;
    //             std::size_t userId_pos;
    //             unsigned long int userId;
    //             std::cout << "Enter User_Id: ";
    //             std::getline(std::cin, userId_Input);
    //             std::cout << "\n";
    //             try
    //             {
    //                 userId = std::stoul(userId_Input, &userId_pos);
    //                 if (userId_pos != userId_Input.length())
    //                 {
    //                     throw std::invalid_argument("Invalid Input, Please Enter The Number! \n");
    //                 }

    //                 auto jobById = manager.getJobById(userId);
    //                 if (!jobById.has_value())
    //                 {
    //                     std::cout << "Invalid ID or Job not available! \n";
    //                     std::cout << "\n";
    //                 }
    //                 else
    //                 {
    //                     JobDetails(*jobById);
    //                 }
    //             }
    //             catch (const std::invalid_argument &)
    //             {
    //                 std::cout << "Error: Invalid Input. Please enter a valid number. \n";
    //             }
    //             catch (const std::out_of_range &)
    //             {
    //                 std::cout << "Error: Input value is too large. \n";
    //             }
    //             break;
    //         }

    //         case 5:
    //         {
    //             std::cout << "Exiting....! \n";
    //             break;
    //         }

    //         default:
    //         {
    //             std::cout << "Invalid Choice\n";
    //             break;
    //         }
    //         }
    //     }
    //     catch (const std::invalid_argument &)
    //     {
    //         std::cout << "Error: Invalid Input. Please enter a valid number. \n";
    //         choice = 0;
    //         continue;
    //     }
    //     catch (const std::out_of_range &)
    //     {
    //         std::cout << "Error: Input value is too large. \n";
    //         choice = 0;
    //         continue;
    //     }

    // } while (choice != 5);

    return 0;
}