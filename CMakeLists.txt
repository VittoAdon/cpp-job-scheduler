cmake_minimum_required(VERSION 3.20)
project(CppJobScheduler)
set(CMAKE_CXX_STANDARD 20)

add_executable(
    job_run 
    src/main.cpp 
    src/job_operations.cpp 
    src/job_executions.cpp
    src/job_display.cpp
    src/execute_work.cpp
)

target_include_directories(job_run PRIVATE include)