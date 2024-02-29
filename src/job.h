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
	//job();
	job(unsigned short ID);
	virtual ~job();
	job(const job &RHS);
	job& operator=(const job &RHS);

	// added getters, setters and other functions :)
	// --taskList_get_set
	void addTask(task t);
	task getTask(unsigned short index);
	// --jobID_get
	unsigned short getJobID();



private:
	unsigned short jobID;
	std::vector<task> taskList;


};

#endif /* JOB_H_ */
