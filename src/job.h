#ifndef JOB_H_
#define JOB_H_

#include <iostream>
#include <vector>
#include "error.h"
#include "task.h"



class job {
public:
	// standard class functions
	job() = delete;
	job(unsigned short ID, std::string jobString);
	virtual ~job();
	job(const job &RHS);
	job& operator=(const job &RHS);
	bool operator<(const job &RHS) const;
	bool operator>(const job &RHS) const;

	void calculateEST(unsigned long long currentTime);
	unsigned long long calculateEST(const task &t);

	bool compareTasksByID(const task &task1, const task &task2);

	void calculateTotalDuration();

	bool isJobDone();

	void checkTaskProgress(unsigned long long time);

	void printJobDetails() const;

	//Getters and Setters:
	bool getJobsAvailable();

	const unsigned short getJobID() const;

	const unsigned long long getTotalJobDuration() const;

	task getTask(unsigned short index);

	task& getNextTask();

private:
	unsigned short jobID;
	unsigned long long totalJobDuration;
	std::vector<task> taskList;

};

std::ostream& operator<<(std::ostream &os, const job &RHS);

#endif /* JOB_H_ */
