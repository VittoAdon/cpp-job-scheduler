#pragma once
#include <string>

struct ExecutionResult
{
    bool Success = false;
    std::string Output;
    std::string Error_Details;
    std::string Suggested_Resolution;
};