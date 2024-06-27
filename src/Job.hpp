#ifndef JOB_HPP_
#define JOB_HPP_

#include <iostream>
#include <vector>
#include <algorithm>
#include "Task.hpp"

class Job
{
public:
    Job(/* no args */);
    Job(unsigned short id, const std::vector<unsigned short> &config);
    ~Job();

    // *** Functions ***:
    void sortTasksByID();

    //*** Calculations ***:
    void calculateEST(timeType &currentTime);
    timeType calculateEST(const Task &t); //Overload, might combine together

    void calculateJobDuration();
    void calculateSlackTime(timeType duration);

    // *** Operators ***:
	Job& operator=(const Job &rhs);
	bool operator<(const Job &rhs) const;
    bool operator>(const Job &rhs) const;

    // *** Getters and Setters ***:
    unsigned short getJobID() const;
    timeType getJobDuration() const;
    timeType getSlackTime() const;
    const std::vector<Task>& getTaskList() const;
    std::vector<Task>& getTaskList();

    bool getTasksAvailable();
    bool getJobDone();
    bool getJobStarted() const;
    Task &getNextTask();

    bool isPreviousTaskDone(const Task &t);

    void printJobDetails() const;

private:
    unsigned short jobID;
    timeType jobDuration;
    timeType slackTime;
    std::vector<Task> taskList;

};

std::ostream& operator<<(std::ostream &os, const Job &job);


#endif /* JOB_HPP_ */