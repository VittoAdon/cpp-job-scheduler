#include <iostream>
#include "job.hpp"
#include "job_manager.hpp"

void JobStatus_Indicator(JobStatus &a){
        switch(a){
        case JobStatus::Pending:
            std::cout<<"Pending";
            break;
        case JobStatus::InProcess:
            std::cout<<"InProcess";
            break;
        case JobStatus::Completed:
            std::cout<<"Completed";
            break;
        case JobStatus::Failed:
            std::cout<<"Failed";
            break;
    }
}

void JobDetails(Job &a){
    std::cout<<a.Job_Id<<"\n";
    std::cout<<a.Job_Name<<"\n";
    JobStatus_Indicator(a.Status);
    std::cout<<"\n";
}

int CalculateSum(int a, int b){
    int c = a + b;
    return c;
}
void Recreate(){
    std::cout<<"This file has been Recreated! \n";
}

int main(){
    JobManager manager;
    Job a = manager.createJob("CalculateSum");
    Job b = manager.createJob("Recreate");

    while(true){
        auto result = manager.getNextJob();
        if(!result.has_value()){
            std::cout<<"No Jobs Available";
            break;
        }
        if(result->Job_Name == "CalculateSum"){
            result->Status = JobStatus::InProcess;
            int answer = CalculateSum(125, 275);
            result->Status = JobStatus::Completed;
            std::cout<<answer<<"\n";
            JobDetails(*result);
        }
        if(result->Job_Name == "Recreate"){
            result->Status = JobStatus::InProcess;
            Recreate();
            result->Status = JobStatus::Completed;
            JobDetails(*result);
        }

    }

    return 0;
}