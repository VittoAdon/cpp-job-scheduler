#pragma once
#include "job.hpp"
#include <queue>
#include <optional>
#include <unordered_map>
#include <string>

class JobManager
{
private:
    unsigned long int Id_tracker = 1;
    std::queue<Job> q;
    std::unordered_map<unsigned long int, Job> jobs;

public:
    Job createJob(const std::string s)
    {
        Job j;
        j.Job_Id = Id_tracker;
        j.Job_Name = s;
        q.push(j);
        jobs[j.Job_Id] = j;
        Id_tracker++;
        return j;
    }

    std::optional<Job> getNextJob()
    {
        if (q.empty())
        {
            return std::nullopt;
        }
        else
        {
            auto a = q.front();
            q.pop();
            return a;
        }
    }

    void updateJobStatus(unsigned long int job_id, JobStatus status)
    {
        if (jobs.find(job_id) != jobs.end())
        {
            jobs[job_id].Status = status;
        }
    }

    std::optional<Job> getJobById(unsigned long int job_id)
    {
        if (jobs.find(job_id) != jobs.end())
        {
            Job result = jobs[job_id];
            return result;
        }
        else
        {
            return std::nullopt;
        }
    }
};