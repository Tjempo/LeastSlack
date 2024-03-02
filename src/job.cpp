/*
 * job.cpp
 *
 *  Created on: 26 feb. 2024
 *      Author: roymu
 */

#include "job.h"
#include <algorithm>

job::job(unsigned short ID, std::string jobString) : jobID(ID), totalJobDuration(0) {
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

// Functions

void job::calculateEST(unsigned long long time) {
        if (getJobsAvailable()) {
        // Sort taskList by task ID for efficient predecessor search
        std::sort(taskList.begin(), taskList.end(), [this](const task& task1, const task& task2) {
            return compareTasksByID(task1, task2);
        });

            // Loop through tasks and calculate EST
            for (size_t i = 0; i < taskList.size(); ++i) {
                // Get the current task reference
                task &currentTask = taskList[i];

                // Calculate and set EST for the current task
                unsigned long long EST = calculateEST(currentTask);
				std::cout << "EST for task " << currentTask.getTaskID() << " is " << EST << std::endl;
                if (EST < time) {
                    std::cout << "WOW! EST is smaller than time! O_o Impossible!" << std::endl;
                } else {
                    currentTask.setEarliestStartTime(EST);
                }
            }
        } else {
            std::cout << "No more jobs available" << std::endl;
			}
}


unsigned long long job::calculateEST(const task &t) {
    if (t.getTaskID() == 0) {
        // For the first task in the job, it can start immediately
		// Feels like a hack, might be bad... We'll see.
        return 0;
    }

    // Find predecessor task
    auto it = std::find_if(taskList.begin(), taskList.end(),
            [&t](const task &a) { return a.getTaskID() == (t.getTaskID() - 1); });

    // Validate if predecessor is found
    if (it == taskList.end()) {
        throw std::runtime_error("Predecessor task not found");
    }

    // Calculate EST using predecessor's earliest start time and duration
    return it->getEarliestStartTime() + it->getDuration();
}






//Compare tasks by taskID

bool job::compareTasksByID(const task& task1, const task& task2) {
    return task1.getTaskID() < task2.getTaskID();
}


//Calculate Duration:

void job::calculateTotalDuration() {
	unsigned long long totalDuration = 0;

    for (const task& currentTask : taskList) {
        totalDuration += currentTask.getDuration();
    }

    this->totalJobDuration = totalDuration;
    std::cout << "Total Duration of Job " << this->jobID << ": " << totalDuration << std::endl;
}


// Getters 


bool job::getJobsAvailable(){
	for(const task &currentTask : taskList){
		if(!currentTask.getCurrentState() == NOT_COMPLETED){
			return false;
		}
		return true;
	}
	return false; //< To avoid compiler warning >
}

task job::getTask(unsigned short index) {
	return this->taskList.at(index);
}

// --jobID_get
unsigned short job::getJobID() {
	return this->jobID;
}

