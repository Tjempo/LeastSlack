/*
 * job.cpp
 *
 *  Created on: 26 feb. 2024
 *      Author: roymu
 */

#include "job.h"

job::job(): jobID(jobCount) {
	this->jobCount++;
}

job::job(const job &RHS): jobID(jobCount) {
	this->jobCount++;
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
	return *this;
}

/*
bool job::operator==(const job& RHS) const {
	if () {
		return true;
	} else {
		return false;
	}
}

bool job::operator<(const job & RHS) const {
	if () {
		return true;
	}
	return false;
}
*/





// functions

void job::addTask(task t) {
	this->taskList.push_back(t);
}

task job::getTask(unsigned short index) {
	return this->taskList.at(index);
}

