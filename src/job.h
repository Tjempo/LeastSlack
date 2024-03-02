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
#include "global.h"
#include "error.h"
#include "task.h"

/* Fucker...
#define task int // placeholder for real task class
*/

class job {
public:
	// standard class functions
	job() = delete;
	job(unsigned short ID, std::string jobString);
	virtual ~job();
	job(const job &RHS);
	job& operator=(const job &RHS);

    void calculateEST(unsigned long long currentTime);
	unsigned long long calculateEST(const task &t);

    bool compareTasksByID(const task &task1, const task &task2);

    void calculateTotalDuration();

    // added getters, setters and other functions :)

    bool getJobsAvailable();

    task getTask(unsigned short index);

    // --jobID_get
	unsigned short getJobID();



private:
	unsigned short jobID;
	unsigned long long totalJobDuration;
	std::vector<task> taskList;


};

#endif /* JOB_H_ */
