#include "job_lifecycle_manager.hpp"
#include "execution_result.hpp"
#include <optional>
#include <chrono>
JobLifeCycleManager::JobLifeCycleManager(JobManager &manager, JobExecutionRecordManager &recordManager) : manager(manager), recordManager(recordManager) {}

std::optional<JobExecutionRecord> JobLifeCycleManager::startExecution(const Job &job)
{

    if (!manager.updateJobStatus(job.Job_Id, JobStatus::InProcess))
    {
        return std::nullopt;
    }
    int attemptNumber = 1;
    auto record = recordManager.create_Record(job.Job_Id, attemptNumber);
    execution_start_time[record.Execution_Id] = std::chrono::steady_clock::now();
    return record;
}

std::optional<JobExecutionRecord> JobLifeCycleManager::completeExecution(unsigned long int Execution_Id, const ExecutionResult &execution_result)
{
    auto result = recordManager.getRecord_ById(Execution_Id);
    if (!result.has_value())
    {
        return std::nullopt;
    }

    if (execution_result.Success)
    {
        if (!manager.updateJobStatus(result->Job_Id, JobStatus::Completed))
        {
            return std::nullopt;
        }
    }
    else
    {
        if (!manager.updateJobStatus(result->Job_Id, JobStatus::Failed))
        {
            return std::nullopt;
        }
    }
    result->Success = execution_result.Success;
    result->Output = execution_result.Output;
    result->Ended_At = std::chrono::system_clock::now();
    result->Error_Details = execution_result.Error_Details;
    result->Suggested_Resolution = execution_result.Suggested_Resolution;

    std::chrono::steady_clock::time_point captured_time;
    auto iterator = execution_start_time.find(Execution_Id);
    if (iterator != execution_start_time.end())
    {
        captured_time = iterator->second;
    }
    else
    {
        return std::nullopt;
    }
    result->Duration = std::chrono::steady_clock::now() - captured_time;

    if (!recordManager.updated_Record(Execution_Id, *result))
    {
        return std::nullopt;
    }

    execution_start_time.erase(Execution_Id);
    return result;
}
