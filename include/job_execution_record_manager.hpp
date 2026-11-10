#pragma once
#include <unordered_map>
#include <optional>
#include <vector>
#include "job_execution_record.hpp"

class JobExecutionRecordManager
{
private:
    unsigned long int Execution_Id_Tracker = 1;
    std::unordered_map<unsigned long int, JobExecutionRecord> execution_map;

public:
    JobExecutionRecord create_Record(unsigned long int Job_Id, int attemptNumber);
    bool updated_Record(unsigned long int Execution_Id, const JobExecutionRecord &updateInfo);
    std::optional<JobExecutionRecord> getRecord_ById(unsigned long int Execution_Id);
    std::vector<JobExecutionRecord> getHistory_ById(unsigned long int Job_Id);
};