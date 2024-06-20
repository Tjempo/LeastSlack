#ifndef JOB_HPP_
#define JOB_HPP_

typedef unsigned long long int timeType;

#include "Task.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

class Job{

private:
    unsigned short id;

    timeType totalDuration;
    timeType slack;

	std::vector<Task> taskList;
	std::vector<Task> finishedTasks;

public:
    Job() = delete;
    Job(unsigned short, const std::vector<unsigned short> &Config);
    ~Job();

    void sortTasksByID();

    timeType calculateEST(Task &t);
    void calculateEST(timeType currentTime);
    void calculateTotalJobDuration();
    void calculateSlack(timeType longestJobDuration);

    bool operator<(const Job &rhs) const;
    Job &operator=(const Job &rhs);

    unsigned short getJobId() const;
    timeType getJobDuration() const;
    const std::vector<Task> &getTasks() const;
    bool getJobDone(timeType currentTime);
    bool checkTaskProgress(timeType time);
    bool startNextTask(unsigned short currentTime);
    Task &getNextTask();
    bool getJobsAvailable();
    void printJobDetails() const;
};

std::ostream& operator <<(std::ostream &os, const Job &job);

#endif // JOB_HPP_