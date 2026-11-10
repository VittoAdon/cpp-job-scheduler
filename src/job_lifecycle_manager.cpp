
#include "job_lifecycle_manager.hpp"
#include <optional>
JobLifeCycleManager::JobLifeCycleManager(JobManager &manager, JobExecutionRecordManager &recordManager) : manager(manager), recordManager(recordManager) {}

std::optional<JobExecutionRecord> JobLifeCycleManager::startExecution(const Job &job)
{

    if (!manager.updateJobStatus(job.Job_Id, JobStatus::InProcess))
    {
        return std::nullopt;
    }
    int attemptNumber = 1;
    auto record = recordManager.create_Record(job.Job_Id, attemptNumber);
    return record;
}