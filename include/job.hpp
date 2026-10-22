#pragma once
#include <string>

enum class JobStatus{
    Pending,
    InProcess,
    Completed,
    Failed
};

struct Job{
    unsigned long int Job_Id ;
    std::string Job_Name;
    JobStatus Status = JobStatus::Pending;
};