#ifndef TASK_HPP_
#define TASK_HPP_

#include <iostream>
#include <string>

typedef unsigned long long timeType;

class Task {
private:
	timeType taskId;
	timeType machineNumber;
	timeType duration;
	timeType EST; //Earliest Start Time
	timeType startTime;
	timeType endTime;

public:
	Task();
    Task(timeType id, timeType machineNr, timeType duration);
	Task(const Task &rhs);
    ~Task();

	//Logic Operators:
    bool operator<(const Task &rhs) const;
	Task& operator=(const Task &rhs);
    bool operator==(const Task &rhs);

    // Getters:
    timeType getTaskId() const;
	timeType getMachineNumber() const;
	timeType getTaskDuration() const;
	timeType getEST() const;
	timeType getStartTime() const;
	timeType getEndTime() const;

	//Dit kan beter
    bool getTaskStarted() const;
    bool getTaskBusy(unsigned short currentTime) const;
    bool getTaskDone(unsigned short currentTime) const;
    void setEST(timeType newEST);
	
    void startTask(unsigned short startTime);
};

std::ostream& operator<<(std::ostream &os, const Task &t);

#endif /* TASK_HPP_ */