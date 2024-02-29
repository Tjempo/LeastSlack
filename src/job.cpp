/*
 * job.cpp
 *
 *  Created on: 26 feb. 2024
 *      Author: roymu
 */

#include "job.h"

job::job(unsigned short ID) :
		jobID(ID) {
}

job::job(const job &RHS) :
		jobID(RHS.jobID), taskList(RHS.taskList) {
}

job::~job() {
	// TODO Auto-generated destructor stub
}

// opperators

job& job::operator=(const job &RHS) {
	if (this == &RHS) {
		std::cout << "this the same" << std::endl;
		return *this;
	}
	this->jobID = RHS.jobID;
	this->taskList = RHS.taskList;
	return *this;
}

// functions

void job::addTask(task t) {
	this->taskList.push_back(t);
}

task job::getTask(unsigned short index) {
	return this->taskList.at(index);
}

// --jobID_get
unsigned short job::getJobID() {
	return this->jobID;
}

