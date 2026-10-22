#include "job.hpp"
#include <queue>
#include <optional>

class JobManager{
    private:
        unsigned long int Id_tracker = 1;
        std::queue<Job> q;
    public:
        Job createJob(const std::string s){
            Job j;
            j.Job_Id = Id_tracker;
            j.Job_Name = s;
            q.push(j);
            Id_tracker++;
            return j;
        }

        std::optional<Job> getNextJob(){
            if(q.empty()){
                return std::nullopt;
            }
            else{
                auto a = q.front();
                q.pop();
                return a;
            }

        }
};