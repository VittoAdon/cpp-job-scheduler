#include <iostream>
#include "job.hpp"
#include "job_manager.hpp"
#include "job_operations.hpp"
#include "job_display.hpp"

void CalculateSum_Execution(Job &result, JobManager &manager)
{
    result.Status = JobStatus::InProcess;
    manager.updateJobStatus(result.Job_Id, result.Status);
    int answer = CalculateSum(125, 275);
    result.Status = JobStatus::Completed;
    manager.updateJobStatus(result.Job_Id, result.Status);
    std::cout << answer << "\n";
    JobDetails(result);
    auto history_result = manager.getJobById(result.Job_Id);
    if (history_result.has_value())
    {
        JobDetails(*history_result);
    }
    std::cout << "\n";
}

void Recreate_Execution(Job &result, JobManager &manager)
{
    result.Status = JobStatus::InProcess;
    manager.updateJobStatus(result.Job_Id, result.Status);
    bool isTrue = Recreate();
    if (isTrue)
    {
        result.Status = JobStatus::Completed;
        manager.updateJobStatus(result.Job_Id, result.Status);
    }
    else
    {
        result.Status = JobStatus::Failed;
        manager.updateJobStatus(result.Job_Id, result.Status);
    }
    JobDetails(result);
    auto history_result = manager.getJobById(result.Job_Id);
    if (history_result.has_value())
    {
        JobDetails(*history_result);
    }
    std::cout << "\n";
}

void Unknown_Execution(Job &result, JobManager &manager)
{
    std::cout << "Unknown Job!\n";
    result.Status = JobStatus::Failed;
    manager.updateJobStatus(result.Job_Id, result.Status);
    JobDetails(result);
    auto history_result = manager.getJobById(result.Job_Id);
    if (history_result.has_value())
    {
        JobDetails(*history_result);
    }
    std::cout << "\n";
}