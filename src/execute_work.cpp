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
            std::cout << "No Jobs Available";
            break;
        }
        if (result->Job_Name == "CalculateSum")
        {
            CalculateSum_Execution(*result, manager);
        }
        else if (result->Job_Name == "Recreate")
        {
            Recreate_Execution(*result, manager);
        }
        else
        {
            Unknown_Execution(*result, manager);
        }
    }
}
