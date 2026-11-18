#pragma once
#include "job_manager.hpp"
#include "job_execution_record_manager.hpp"
#include "execution_result.hpp"
#include <chrono>
#include <unordered_map>

class JobLifeCycleManager
{
private:
    JobManager &manager;
    JobExecutionRecordManager &recordManager;
    std::unordered_map<unsigned long int, std::chrono::steady_clock::time_point> execution_start_time;

public:
    JobLifeCycleManager(JobManager &manager, JobExecutionRecordManager &recordManager);
    std::optional<JobExecutionRecord> startExecution(const Job &job);
    std::optional<JobExecutionRecord> completeExecution(unsigned long int Execution_Id, const ExecutionResult &execution_result);
};