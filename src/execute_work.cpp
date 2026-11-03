#include <iostream>
#include "execute_work.hpp"
#include "job_execution.hpp"

void execute_work(JobManager &manager)
{
    while (true)
    {
        auto result = manager.getNextJob();

        if (!result.has_value())
        {
            std::cout << "No Jobs Available\n";
            std::cout << "\n";
            break;
        }
        if (result->Type == JobType::CalculateSum)
        {
            CalculateSum_Execution(*result, manager);
        }
        else if (result->Type == JobType::RecreateFile)
        {
            Recreate_Execution(*result, manager);
        }
        else
        {
            Unknown_Execution(*result, manager);
        }
    }
}
