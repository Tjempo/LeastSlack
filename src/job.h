/*
 * job.h
 *
 *  Created on: 26 feb. 2024
 *      Author: roymu
 */

#ifndef JOB_H_
#define JOB_H_

#include <iostream>
#include <vector>
#include "error.h"
//#include "task.h"
#define task int // placeholder for real task class

class job {
public:
	// standard class functions
	job();
	virtual ~job();
	job(const job &RHS);
	job& operator=(const job &RHS);
	bool operator==(const job& RHS) const;
	bool operator<(const job & RHS) const;

	// added getters, setters and other functions :)
	// --taskList
	void addTask(task t);
	task getTask(unsigned short index);

private:
	static unsigned short jobCount;
	unsigned short jobID;
	std::vector<task> taskList;


};

#endif /* JOB_H_ */
