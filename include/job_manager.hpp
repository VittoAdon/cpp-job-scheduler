#pragma once
#include "job.hpp"
#include <queue>
#include <optional>
#include <unordered_map>
#include <string>
#include <vector>

class JobManager
{
private:
    unsigned long int Id_tracker = 1;
    std::queue<Job> q;
    std::unordered_map<unsigned long int, Job> jobs;

public:
    Job createJob(const JobType Type);

    std::optional<Job> getNextJob();

    bool updateJobStatus(unsigned long int job_id, JobStatus status);

    std::optional<Job> getJobById(unsigned long int job_id);

    std::vector<Job> getAllJob() const;
};