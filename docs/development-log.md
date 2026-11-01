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

**GitHub Status** Pushed

### Session 5 - Improving Job Status Validation and Execution Consistency

**Objectives**

- The previous implementation updated job statuses without checking whether the job ID existed in the registry.
- There was a need to validate status updates and prevent execution when a job could not be found.
- Ensure `JobManager` remains the single source of truth for the latest job status.
- Keep generated files such as `job_report.txt` out of the GitHub repository.

**Implementation**

- Changed `updateJobStatus(unsigned long int job_id, JobStatus status)` in `job_manager.hpp` from `void` to `bool`.
- The function now returns `true` when the job ID exists in the `jobs` hash map and its status is updated; otherwise, it returns `false`.
- Updated `CalculateSum_Execution()` to check the result of `manager.updateJobStatus(result.Job_Id, JobStatus::InProcess)`. If the update fails, the function returns immediately without executing the calculation.
- Applied the same initial status validation pattern to `Recreate_Execution()` and `Unknown_Execution()`.
- In `CalculateSum_Execution()`, the job status is updated to `Completed` after the calculation.
- In `Recreate_Execution()`, the job status is updated to `Completed` if the report-writing operation succeeds, or `Failed` if it fails.
- In `Unknown_Execution()`, the job is marked `Failed` only after the initial status update succeeds.
- Used `manager.getJobById(result.Job_Id)` and `has_value()` to retrieve and display the latest job record from the registry.
- Tested the updated implementation by building and running the project.
- Updated `.gitignore` to ignore `/job_report.txt`, preventing the generated report from appearing as an untracked file.

**Outcome**

- The project compiled successfully using CMake.
- `CalculateSum` executed successfully and returned `400`, with its final status displayed as `Completed`.
- `Recreate` successfully generated the report, and its final status was displayed as `Completed`.
- `UnknowTask` was identified as an unknown job and its status was displayed as `Failed`.
- The scheduler processed all three jobs and displayed `No Jobs Available` after the queue was exhausted.
- Job status validation is now more consistent across the execution functions.
- The registry continues to store the latest job status rather than a complete history of status transitions.

**GitHub Status:** Pushed

### Session 6 - Refactoring Job Dispatch into a Separate Component

**Objectives**

- The previous implementation had queue processing and job-name comparisons directly inside `main.cpp`.
- As the number of job types grows, keeping all dispatch logic in `main.cpp` would make the code harder to maintain and debug.
- Keep `main.cpp` focused on connecting components and coordinating the application.
- Introduce a separate component to handle queue processing and dispatch jobs to their respective execution functions.

**Implementation**

- Created `include/execute_work.hpp` to declare the `execute_work()` function.
- Declared the function as `void execute_work(JobManager &manager);`, passing `JobManager` by reference to access the existing queue and registry without creating a copy.
- Created `src/execute_work.cpp` to implement the queue-processing and dispatch logic.
- Moved the `while` loop from `main.cpp` into `execute_work()`.
- Used `manager.getNextJob()` to retrieve jobs from the FIFO queue.
- Used `has_value()` to check whether a job was retrieved. If the queue was empty, the function displayed `No Jobs Available` and terminated the loop.
- Moved the existing job-name comparisons into `execute_work.cpp`:
  - `CalculateSum` calls `CalculateSum_Execution()`.
  - `Recreate` calls `Recreate_Execution()`.
  - Unrecognized job names call `Unknown_Execution()`.
- Updated `main.cpp` to create the jobs and call `execute_work(manager)` instead of processing the queue directly.
- Updated `CMakeLists.txt` to include `src/execute_work.cpp` in the executable build.
- Initially encountered a linker error, `undefined reference to execute_work(JobManager&)`, because the new source file was not included in the build configuration. Added the source file to CMake and rebuilt successfully.

**Outcome**

- The project compiled successfully using CMake.
- All three jobs executed with their expected results:
  - `CalculateSum` returned `400` and finished with status `Completed`.
  - `Recreate` successfully generated the report and finished with status `Completed`.
  - `UnknowTask` was identified as an unknown job and finished with status `Failed`.
- The queue was processed until empty, displaying `No Jobs Available`.
- Job dispatch and queue processing were separated from `main.cpp`, improving code organization and making future maintenance easier.
- The dispatch mechanism still uses an `if/else` chain. Improving dispatch scalability remains a future task.
- Identified the next development milestone: create an interactive CLI so users can submit jobs dynamically instead of relying on hardcoded jobs.

**GitHub Status:** Pushed

# Session 7 – Building an Interactive CLI for the C++ Job Scheduler

## 1. Objective

Transform the existing hardcoded Job Scheduler into an interactive command-line application (CLI), allowing users to submit, process, view, and search jobs through a menu-driven interface.

## 2. Implementation

### 2.1. Interactive CLI Menu

Implemented a menu-driven interface using:
- `do-while` loop to keep the application running.
- `switch-case` to handle user selections.
- `std::cin` and `std::cout` for user interaction.
- `JobManager` instance maintained outside the loop to preserve application state.

Available operations:

1. Submit a job
2. Process queue
3. View all jobs
4. Find job by ID
5. Exit

### 2.2. Job Submission

Implemented interactive job selection.

Supported job types:
- CalculateSum
- Recreate

Used the existing `JobManager::createJob()` function to create jobs and add them to the processing queue and job registry.

Added submission confirmation messages and invalid job selection handling.

### 2.3. Queue Processing

Integrated the existing `execute_work()` function into the CLI.

- Reused the Session 6 job dispatch implementation.
- Processed pending jobs through the existing execution functions.
- Handled empty queue conditions.
- Allowed users to submit and process additional jobs without restarting the application.

### 2.4. View All Jobs

Implemented `getAllJob()` in `JobManager`.

Key concepts applied:
- `std::vector<Job>` to store a temporary collection of job copies.
- `std::unordered_map` iteration using a range-based for loop.
- `const auto&` to avoid unnecessary copies during iteration.
- `empty()` to check whether jobs are available.
- Reused `JobDetails()` to display job information.

Important design decision:

The unordered map remains the source of truth for job records. The vector contains temporary copies for displaying jobs and does not modify the original registry or processing queue.

### 2.5. Find Job by ID

Integrated the existing `getJobById()` function.

Implemented:
- User input for Job ID.
- Job lookup through the registry.
- `std::optional<Job>` to represent a potentially missing job.
- `has_value()` to check whether a job exists.
- Dereferencing the optional to display the retrieved job.
- Error handling for nonexistent job IDs.

### 2.6. Const Correctness

Updated the display function interfaces to support read-only access:

- `JobDetails(const Job &a)`
- `JobStatus_Indicator(const JobStatus &a)`

This prevents accidental modification of job information during display operations.

### 2.7. C++ Header and Source File Concepts

Discussed the difference between declarations and definitions.

- `.hpp`: Interfaces, class declarations, member variables, and function declarations.
- `.cpp`: Actual function implementations.

Discussed why `JobManager` currently has implementations inside its header and why separating them into a source file will improve maintainability as the project grows.

## 3. Testing and Verification

Successfully tested the following scenarios:

| Test | Result |
|---|---|
| Submit CalculateSum | Successful |
| Submit Recreate | Successful |
| View all pending jobs | Successful |
| Find existing job by ID | Successful |
| Process multiple jobs | Successful |
| Verify completed statuses | Successful |
| Process an empty queue | Handled |
| View jobs after processing | Successful |
| Search for nonexistent ID | Handled |
| Submit additional jobs after processing | Supported |
| Exit application | Successful |


## 4. Session Outcome

Successfully transformed the previous hardcoded Job Scheduler into an interactive CLI application.

The application can now:
- Submit different job types.
- Maintain a processing queue.
- Execute pending jobs.
- Track job statuses.
- Display all registered jobs.
- Search for individual jobs by ID.
- Continue operating after queue processing.

**GitHub Status:** Pushed

# C++ Job Scheduler — Session 8

## 1. Objectives

- Implement robust input validation across the interactive CLI.
- Handle invalid, partially numeric and out-of-range user inputs.
- Understand and implement C++ exception handling using `try`, `catch` and `throw`.
- Prevent invalid inputs from interrupting application execution or causing unintended termination.
- Improve variable scope, code structure and readability.
- Verify that existing job management and execution functionality remains stable.

## 2. Implementation

### 2.1 Input Validation

Implemented input validation for all three user input paths:

- Main menu selection using `std::stoi()`.
- Job selection using `std::stoi()`.
- Job ID lookup using `std::stoul()`.

Used `std::getline()` to read complete input lines and the position parameter of conversion functions to identify partially numeric inputs.

For example, inputs such as `5abc` and `1abc` are rejected instead of being accepted as valid numbers.

### 2.2 Exception Handling — Try, Catch and Throw

Implemented C++ exception handling to manage invalid user inputs safely.

**`try` block**
- Encloses numeric conversion and input validation operations.
- Allows exceptions generated during conversion or explicitly thrown during validation to be handled.

**`throw` statement**
- Used `throw std::invalid_argument()` when the conversion function successfully parsed a numeric prefix but additional characters remained.
- This ensures partially numeric inputs are rejected.

**`catch` blocks**
- `std::invalid_argument`: Handles inputs that cannot be converted into valid numbers or fail the complete-input validation check.
- `std::out_of_range`: Handles numeric values exceeding the supported range.

Replaced generic exception messages with meaningful messages to improve CLI usability.

### 2.3 Control-Flow Correction

Identified and corrected an issue where entering `5abc` could unintentionally terminate the application.

Although `std::stoi()` initially converts the input to `5`, the subsequent position check detects invalid trailing characters and throws an exception.

Resetting the menu choice to `0` inside the main menu exception handlers ensures that invalid input cannot satisfy the exit condition.

### 2.4 Code Cleanup

- Moved variables closer to their respective usage scopes.
- Removed unnecessary variable declarations.
- Removed unnecessary `else` blocks following `throw` statements.
- Improved exception messages.
- Improved code formatting and readability.

## 3. Testing and Verification

Successfully tested the following scenarios:

- Submitted `CalculateSum` and `Recreate` jobs.
- Rejected alphabetic and partially numeric menu inputs.
- Rejected invalid job selections.
- Verified job lookup using valid and invalid IDs.
- Tested empty and out-of-range numeric inputs.
- Verified invalid exit input such as `5abc` does not terminate the application.
- Processed queued jobs successfully.
- Verified job statuses changed from `Pending` to `Completed`.
- Confirmed updated job information remained available after execution.
- Verified normal application termination using menu option `5`.

## 4. Outcomes

- Implemented robust basic input validation across the interactive CLI.
- Gained practical experience with `std::stoi()`, `std::stoul()` and their position parameters.
- Applied C++ exception handling using `try`, `catch` and `throw`.
- Understood the difference between `std::invalid_argument` and `std::out_of_range`.
- Improved control-flow reliability by handling invalid inputs without unintended application termination.
- Improved variable scope and overall code readability.
- Verified that job submission, lookup, queue processing and status management continue to function correctly.

**GitHub Status:** Pushed

