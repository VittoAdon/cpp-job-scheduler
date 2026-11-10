#include "job_execution_record_manager.hpp"

JobExecutionRecord JobExecutionRecordManager::create_Record(unsigned long int Job_Id, int attemptNumber)
{
    JobExecutionRecord execution_records;

    execution_records.Execution_Id = Execution_Id_Tracker;
    execution_records.Job_Id = Job_Id;
    execution_records.Attempt_Number = attemptNumber;
    execution_records.Started_At = std::chrono::system_clock::now();

    execution_map[execution_records.Execution_Id] = execution_records;
    Execution_Id_Tracker++;

    return execution_records;
}

bool JobExecutionRecordManager::updated_Record(unsigned long int Execution_Id, const JobExecutionRecord &updatedInfo)
{
    auto iterator = execution_map.find(Execution_Id);
    if (iterator != execution_map.end())
    {
        iterator->second = updatedInfo;
        return true;
    }
    return false;
}

std::optional<JobExecutionRecord> JobExecutionRecordManager::getRecord_ById(unsigned long int Execution_Id)
{
    auto iterator = execution_map.find(Execution_Id);
    if (iterator != execution_map.end())
    {
        return iterator->second;
    }
    else
    {
        return std::nullopt;
    }
}

std::vector<JobExecutionRecord> JobExecutionRecordManager::getHistory_ById(unsigned long int Job_Id)
{

    std::vector<JobExecutionRecord> result;
    for (const auto &[execution_id, records] : execution_map)
    {
        if (records.Job_Id == Job_Id)
        {
            result.push_back(records);
        }
    }
    return result;
}