#pragma once
#include <string>

enum class JobStatus
{
    Pending,
    InProcess,
    Completed,
    Failed
};
enum class JobType
{
    CalculateSum,
    RecreateFile
};

struct Job
{
    unsigned long int Job_Id;
    JobType Type;
    JobStatus Status = JobStatus::Pending;
};