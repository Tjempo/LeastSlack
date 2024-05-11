#ifndef TASK_HPP_
#define TASK_HPP_

#include <iostream>
#include <string>

typedef unsigned long long timeUnit;

class Task {
private:
	timeUnit taskId;
	timeUnit machineNumber;
	timeUnit duration;
	timeUnit EST; //Earliest Start Time
	timeUnit startTime;
	timeUnit endTime;

public:
	Task();
    Task(timeUnit id, timeUnit machineNr, timeUnit duration);
    ~Task();

	//Logic Operators:
    bool operator<(const Task &rhs) const;
	Task& operator=(const Task &rhs);
    bool operator==(const Task &rhs);

    // Getters:
    timeUnit getTaskId() const;
	timeUnit getMachineNumber() const;
	timeUnit getDuration() const;
	timeUnit getEST() const;
	timeUnit getStartTime() const;
	timeUnit getEndTime() const;
};

#endif /* TASK_HPP_ */