# C++ Job Scheduler
## Engineering Development Log

**Project Type:** C++ Application Development  
**Language Standard:** C++20  
**Development Environment:** Ubuntu Linux, VS Code, GCC  
**Version Control:** Git and GitHub  
**Repository:** [VittoAdon/cpp-job-scheduler](https://github.com/VittoAdon/cpp-job-scheduler)

---

## 1. Project Objective

Develop a C++ job scheduling application that creates jobs, assigns unique identifiers, queues jobs using FIFO ordering, dispatches supported operations, and tracks execution outcomes.

The project will progressively introduce maintainable architecture, error handling, automated testing, persistence, and concurrent execution.

## 2. Development Environment

| Component | Tool |
|---|---|
| Operating System | Ubuntu Linux |
| Programming Language | C++20 |
| Compiler | GCC / g++ |
| Editor | Visual Studio Code |
| Version Control | Git |
| Remote Repository | GitHub |

## 3. Development History

### Session 1 — Foundation and Version Control

**Objectives**
- Establish the initial project structure.
- Implement the basic job model and FIFO queue.
- Configure Git and GitHub.

**Implementation**
- Created the `Job` structure and `JobStatus` enumeration.
- Implemented `JobManager` using `std::queue`.
- Added job creation, ID assignment, and FIFO retrieval.
- Implemented basic operation dispatch in `main.cpp`.
- Initialized Git and pushed the initial commit.

**Outcome**

The initial scheduler successfully executed queued jobs in FIFO order.

**Git Checkpoint:** `a8102dd` — Add Initial FIFO Job Scheduler

### Session 2 — File Operations and Error Handling

**Objectives**
- Introduce a real file operation.
- Handle operation success and failure.
- Handle unsupported job types.

**Implementation**
- Added file creation using `std::ofstream`.
- Created `job_report.txt` and wrote report content.
- Changed `Recreate()` to return a Boolean result.
- Updated job status based on the operation result.
- Added handling for unknown job types.

**Verification**
- `CalculateSum` produced the expected result of `400`.
- `Recreate` created the report file successfully.
- An unknown job type was marked as `Failed`.

**Outcome**

Basic file I/O, operation-result handling, and unknown-job handling were implemented and manually tested.

**Git Checkpoint:** pushed

### Session 3 - Updating the code with hash_map to register history of work

**Objectives**
 - previous code was not tracking the history of the job done.
 - So there is a necessity to track the history of the job later in future to address an problem or for any other reason.
 
**Implementation**
 - ` jobs[j.Job_Id] = j;` Jobs(id, name, status) are now pushed to jobs(hasp_map) in createJob. 
 - Used `std::unordered_map<unsigned long int, Job> jobs` hash_map as key is job_id and Job is struc with id, name and status.
 - Created a function `void updateJobStatus(unsigned long int job_id, JobStatus status)` this update the job status by the job id searched from the hash_map(register).
 - To retrive the job history from the hash_map `std::optional<Job> getJobById(unsigned long int job_id)` used this function.
 - Then in main.cpp using manager the JobStatus is updated in hash_map with `manager.updateJobStatus(result->Job_Id, result->Status);` 
 - Then job history is displayed with optional ` auto history_result = manager.getJobById(result->Job_Id);` by checking the job is present using `has_value()` then displayed with `JobDetails(*history_result)`.

**Outcome**
 - The result came as expected with queue extracting the job and preforming the work.
 - Then job is also updated hash_map for the history record.
 - Also history is retrived from the hash_map and displayed.

 **GitHub Status** Pushed

 ### Session 4 - Code CleanUp

 **Objective**
  - The goal is to make the code looks clean.

**Implementation**
  - Implemented new header files `job_display.hpp`, `job_executions.hpp`, `job_operations.hpp`.
  - Implemented new source files `job_display.cpp`, `job_executions.cpp`, `job_operations.cpp`.
  - Cleaned up `main.cpp` file.

**Outcome**
  - Code cleaned up as expected.
  