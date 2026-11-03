#include "job_manager.hpp"

Job JobManager::createJob(const JobType Type)
{
    Job j;
    j.Job_Id = Id_tracker;
    j.Type = Type;
    q.push(j);
    jobs[j.Job_Id] = j;
    Id_tracker++;
    return j;
}

std::optional<Job> JobManager::getNextJob()
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

bool JobManager::updateJobStatus(unsigned long int job_id, JobStatus status)
{
    if (jobs.find(job_id) != jobs.end())
    {
        jobs[job_id].Status = status;
        return true;
    }
    return false;
}

std::optional<Job> JobManager::getJobById(unsigned long int job_id)
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

std::vector<Job> JobManager::getAllJob() const
{
    std::vector<Job> viewJobs;
    for (const auto &pair : jobs)
    {
        viewJobs.push_back(pair.second);
    }
    return viewJobs;
}