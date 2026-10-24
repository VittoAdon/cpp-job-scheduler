#include <iostream>
#include "job.hpp"
#include "job_manager.hpp"
#include "job_execution.hpp"

int main()
{
    JobManager manager;
    Job a = manager.createJob("CalculateSum");
    Job b = manager.createJob("Recreate");
    Job c = manager.createJob("UnknowTask");

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

    return 0;
}