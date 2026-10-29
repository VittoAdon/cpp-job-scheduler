#include <iostream>
#include "job.hpp"
#include "job_manager.hpp"
#include "job_execution.hpp"
#include "execute_work.hpp"

int main()
{
    JobManager manager;
    Job a = manager.createJob("CalculateSum");
    Job b = manager.createJob("Recreate");
    Job c = manager.createJob("UnknowTask");
    execute_work(manager);
    return 0;
}