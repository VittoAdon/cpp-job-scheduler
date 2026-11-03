#include <iostream>
#include "job_display.hpp"

void JobStatus_Indicator(const JobStatus &a)
{
    switch (a)
    {
    case JobStatus::Pending:
        std::cout << "Pending";
        break;
    case JobStatus::InProcess:
        std::cout << "InProcess";
        break;
    case JobStatus::Completed:
        std::cout << "Completed";
        break;
    case JobStatus::Failed:
        std::cout << "Failed";
        break;
    }
}

void JobType_Indicator(const JobType &Type)
{
    switch (Type)
    {
    case JobType::CalculateSum:
        std::cout << "CalculateSum";
        break;
    case JobType::RecreateFile:
        std::cout << "RecreateFile";
        break;

    default:
        std::cout << "Unknown Job Type";
        break;
    }
}

void JobDetails(const Job &a)
{
    std::cout << a.Job_Id << "\n";
    JobType_Indicator(a.Type);
    std::cout << "\n";
    JobStatus_Indicator(a.Status);
    std::cout << "\n";
}