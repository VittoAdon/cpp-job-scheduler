#pragma once
#include "job_manager.hpp"
#include "job_execution_record_manager.hpp"

class JobLifeCycleManager
{
private:
    JobManager &manager;
    JobExecutionRecordManager &recordManager;

public:
    JobLifeCycleManager(JobManager &manager, JobExecutionRecordManager &recordManager);
    std::optional<JobExecutionRecord> startExecution(const Job &job);
};