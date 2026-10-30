#include <iostream>
#include "job.hpp"
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

void JobDetails(const Job &a)
{
    std::cout << a.Job_Id << "\n";
    std::cout << a.Job_Name << "\n";
    JobStatus_Indicator(a.Status);
    std::cout << "\n";
}