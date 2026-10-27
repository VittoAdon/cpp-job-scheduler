#include <iostream>
#include "job.hpp"
#include "job_manager.hpp"
#include "job_operations.hpp"
#include "job_display.hpp"

void CalculateSum_Execution(Job &result, JobManager &manager)
{
    if (!manager.updateJobStatus(result.Job_Id, JobStatus::InProcess))
    {
        return;
    }
    int answer = CalculateSum(125, 275);
    manager.updateJobStatus(result.Job_Id, JobStatus::Completed);
    std::cout << answer << "\n";
    auto history_result = manager.getJobById(result.Job_Id);
    if (history_result.has_value())
    {
        JobDetails(*history_result);
    }
    std::cout << "\n";
}

void Recreate_Execution(Job &result, JobManager &manager)
{
    if (!manager.updateJobStatus(result.Job_Id, JobStatus::InProcess))
    {
        return;
    }
    bool isTrue = Recreate();
    if (isTrue)
    {
        manager.updateJobStatus(result.Job_Id, JobStatus::Completed);
    }
    else
    {
        manager.updateJobStatus(result.Job_Id, JobStatus::Failed);
    }
    auto history_result = manager.getJobById(result.Job_Id);
    if (history_result.has_value())
    {
        JobDetails(*history_result);
    }
    std::cout << "\n";
}

void Unknown_Execution(Job &result, JobManager &manager)
{
    if (!manager.updateJobStatus(result.Job_Id, JobStatus::Failed))
    {
        return;
    }
    std::cout << "Unknown Job!\n";
    auto history_result = manager.getJobById(result.Job_Id);
    if (history_result.has_value())
    {
        JobDetails(*history_result);
    }
    std::cout << "\n";
}