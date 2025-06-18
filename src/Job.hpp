#ifndef JOB_HPP_
#define JOB_HPP_

#include <algorithm>
#include <iostream>
#include <vector>

#include "Task.hpp"

class Job {
   public:
    Job(/* no args */);
    Job(unsigned short id, const std::vector<unsigned short> &config);
    ~Job();

    // *** Functions ***:

    /// @brief checks the tasklist if there are tasks that are done. If they are mark them as done.
    /// @param currentTime time of the simulation
    void checkTaskProgress(const timeType &currentTime);

    //*** Calculations ***:

    /// @brief Calculates the Earliest Start Time for each task in the taskList
    void calculateEST(timeType &currentTime);

    /// @brief Calculates the Earliest Start Time for a specific task
    timeType calculateEST(const Task &t);  // Overloaded function

    /// @brief Calculates the duration of the job
    void calculateJobDuration();

    /// @brief Calculates the slack time of the job
    void calculateSlackTime(timeType duration);

    // *** Operators ***:
    Job &operator=(const Job &RHS);
    bool operator<(const Job &RHS) const;
    bool operator>(const Job &RHS) const;


    // *** Getters and Setters ***:
    unsigned short getJobID() const;
    timeType getJobDuration() const;
    timeType getSlackTime() const;
    const std::vector<Task> &getTaskList() const;
    std::vector<Task> &getTaskList();

    bool getTasksAvailable() const;
    bool getJobDone() const;
    Task &getNextTask();

    
    bool isPreviousTaskDone(const Task &t);

    // *** Not used in the current implementation ***:
    void printJobDetails() const;

   private:
    unsigned short jobID;
    timeType jobDuration;
    timeType slackTime;
    std::vector<Task> taskList;

    // *** Functions ***:
    void sortTasksByID();
};

// *** Stream Operator ***:

// Does not need to be a friend function, as it only uses public get-functions.
std::ostream &operator<<(std::ostream &os, const Job &job);

#endif /* JOB_HPP_ **/