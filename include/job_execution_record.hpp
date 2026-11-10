#pragma once
#include <string>
#include <chrono>

struct JobExecutionRecord
{
    unsigned long int Execution_Id = 0;
    unsigned long int Job_Id = 0;
    int Attempt_Number = 0;
    std::chrono::system_clock::time_point Started_At;
    std::chrono::system_clock::time_point Ended_At;
    std::chrono::steady_clock::duration Duration;
    bool Success = false;
    std::string Output;
    std::string Error_Details;
    std::string Suggested_Resolution;
};
