#ifndef TASK_HPP_
#define TASK_HPP_

#include <iostream>
#include <string>

typedef unsigned long long timeType;

enum taskState {NOT_STARTED, STARTED, DONE};

class Task {
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
	taskState getTaskState() const;
	bool getTaskStarted() const;

	// Setters:
    void setEST(timeType newEST);
	void setTaskDone();
	
	// Other Functions:
    void startTask(unsigned short startTime);
	
private:
	timeType taskId;
	timeType machineNumber;
	timeType duration;
	timeType EST; //Earliest Start Time
	timeType startTime;
	timeType endTime;
	taskState state;
};

std::ostream& operator<<(std::ostream &os, const Task &t);

#endif /* TASK_HPP_ */