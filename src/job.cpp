/*
 * job.cpp
 *
 *  Created on: 26 feb. 2024
 *      Author: roymu
 */

#include "job.h"

job::job(unsigned short ID, std::string jobString) : jobID(ID) {
	// Define & initialize variables
	std::istringstream iss(jobString);
    unsigned short machineID = 0; 
	unsigned short duration = 0;	
	unsigned short taskID = 0;

    // Loop to read pairs of machineID and duration from jobString
    while (iss >> machineID >> duration) {
        taskList.push_back(task(taskID++, machineID, duration));
		std::cout << "TaskID: " << taskID << std::endl;
		std::cout << "MachineID: " << machineID << " Duration: " << duration << std::endl;
	}
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

task job::getTask(unsigned short index) {
	return this->taskList.at(index);
}

// --jobID_get
unsigned short job::getJobID() {
	return this->jobID;
}

