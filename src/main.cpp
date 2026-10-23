#include <iostream>
#include "job.hpp"
#include "job_manager.hpp"
#include <fstream>

void JobStatus_Indicator(JobStatus &a)
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

void JobDetails(Job &a)
{
    std::cout << a.Job_Id << "\n";
    std::cout << a.Job_Name << "\n";
    JobStatus_Indicator(a.Status);
    std::cout << "\n";
}

int CalculateSum(int a, int b)
{
    int c = a + b;
    return c;
}
bool Recreate()
{
    std::ofstream file("job_report.txt");
    if (!file.is_open())
    {
        std::cout << "Failed to Open!\n";
        return false;
    }
    file << "Job has been filed in this report! \n";
    file.close();
    if (!file)
    {
        std::cout << "Failed to Write!\n";
        return false;
    }
    return true;
}

int main()
{
    JobManager manager;
    Job a = manager.createJob("CalculateSum");
    Job b = manager.createJob("Recreate");
    Job c = manager.createJob("UnknowTask");

    while (true)
    {
        auto result = manager.getNextJob();

        if (!result.has_value())
        {
            std::cout << "No Jobs Available";
            break;
        }
        if (result->Job_Name == "CalculateSum")
        {
            result->Status = JobStatus::InProcess;
            manager.updateJobStatus(result->Job_Id, result->Status);
            int answer = CalculateSum(125, 275);
            result->Status = JobStatus::Completed;
            manager.updateJobStatus(result->Job_Id, result->Status);
            std::cout << answer << "\n";
            JobDetails(*result);
            auto history_result = manager.getJobById(result->Job_Id);
            if (history_result.has_value())
            {
                JobDetails(*history_result);
            }
            std::cout << "\n";
        }
        else if (result->Job_Name == "Recreate")
        {
            result->Status = JobStatus::InProcess;
            manager.updateJobStatus(result->Job_Id, result->Status);
            bool isTrue = Recreate();
            if (isTrue)
            {
                result->Status = JobStatus::Completed;
                manager.updateJobStatus(result->Job_Id, result->Status);
            }
            else
            {
                result->Status = JobStatus::Failed;
                manager.updateJobStatus(result->Job_Id, result->Status);
            }
            JobDetails(*result);
            auto history_result = manager.getJobById(result->Job_Id);
            if (history_result.has_value())
            {
                JobDetails(*history_result);
            }
            std::cout << "\n";
        }
        else
        {
            std::cout << "Unknown Job!\n";
            result->Status = JobStatus::Failed;
            manager.updateJobStatus(result->Job_Id, result->Status);
            JobDetails(*result);
            auto history_result = manager.getJobById(result->Job_Id);
            if (history_result.has_value())
            {
                JobDetails(*history_result);
            }
            std::cout << "\n";
        }
    }

    return 0;
}