#include "job.h"
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <memory>

job::job(unsigned short ID, std::string jobString) :
		jobID(ID), totalJobDuration(0) {
	// Define & initialize variables
	std::istringstream iss(jobString);
	unsigned short machineID = 0;
	unsigned short duration = 0;
	unsigned short taskID = 0;

	// Loop to read pairs of machineID and duration from jobString
	while (iss >> machineID >> duration) {
		taskList.push_back(task(++taskID, machineID, duration));
	}
}

job::job(const job &RHS) :
    jobID(RHS.jobID), totalJobDuration(RHS.totalJobDuration) {
    for (const task& task : RHS.taskList) {
        this->taskList.push_back(task);
    }
}


job::~job() {
	// Destructor stub
}

// Operators:
job& job::operator=(const job &RHS) {
    if (this == &RHS) {
        return *this;
    } else {
        this->jobID = RHS.getJobID();
        this->totalJobDuration = RHS.getTotalJobDuration();
        this->taskList = RHS.taskList; // This involves copying
        return *this;
    }
}


bool job::operator<(const job &RHS) const {
	if (this->getTotalJobDuration() < RHS.getTotalJobDuration()) {
		return true;
	}else if (this->getTotalJobDuration() == RHS.getTotalJobDuration()) {
		if (this->getJobID() > RHS.getJobID()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool job::operator>(const job &RHS) const {
	if (this->getTotalJobDuration() > RHS.getTotalJobDuration()) {
		return true;
	} else if (this->getTotalJobDuration() == RHS.getTotalJobDuration()) {
		if (this->getJobID() > RHS.getJobID()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

// Functions

void job::sortByTaskID(){
	std::sort(this->taskList.begin(), this->taskList.end());
}

//Time Calculations:
void job::calculateEST(unsigned long long time) {
	if (getJobsAvailable()) {
		sortByTaskID();

		for (size_t i = 0; i < taskList.size(); ++i) {
			task &currentTask = taskList[i];
			unsigned long long EST = calculateEST(currentTask) + time;
			currentTask.setEarliestStartTime(EST);
		}
	} else {
//		std::cout << "No more jobs available" << std::endl;
	}
}

unsigned long long job::calculateEST(const task &t) {
	auto getPreviousTask = [&t](const task &ts) {
		return ts.getTaskID() == (t.getTaskID() - 1);
	};

	// Find the previous task
	auto previousTaskID = std::find_if(taskList.begin(), taskList.end(),getPreviousTask);
	// If the previous task is not found, it means the current task is the first task

	if (previousTaskID == taskList.end()) {
		// If it is, it can start immediately
		return 0;
	}
	// Calculate EST using predecessor's earliest start time and duration
	return (previousTaskID->getEarliestStartTime() + previousTaskID->getDuration());
}

//Calculate Duration:

void job::calculateTotalDuration() {
	sortByTaskID();
	//Dan pakken we het laatste item in de taskList
	auto previousTask = std::prev(taskList.end());
	this->totalJobDuration = (previousTask->getDuration() + previousTask->getEarliestStartTime());
}

bool job::isJobDone() {
	for (task &currentTask : taskList) {
		//Count amount of unfinished tasks:
		if (currentTask.getCurrentState() != COMPLETED) {
			return false;
		}
	}
	return true;
}

// Getters 

bool job::getJobsAvailable() {
	for (const task &currentTask : taskList) {
		if (!currentTask.getCurrentState() == NOT_COMPLETED) {
			return false;
		}
		return true;
	}
	return false; //< To avoid compiler warning >
}

const task& job::getTask(unsigned short index) const {
    return this->taskList.at(index);
}


//Ik denk dat het hier niet goed gaat:
task& job::getNextTask() {
    sortByTaskID();

    for (unsigned short i = 0; i < taskList.size(); ++i) {
        if (taskList[i].getCurrentState() != COMPLETED) {
            return taskList[i];
        }
    }

    // If all tasks are completed, return the first task (the one with the lowest task ID)
    // Assuming that a job always has at least one task
    // If a job might have no tasks, you should handle that case separately
    // (e.g., throw an exception or return a special value)
    //std::cout << "job::getNextTask - end" << std::endl;
    return taskList.front();
}


void job::checkTaskProgress(unsigned long long time) {
	for (task &task : taskList) {
		if (task.getCurrentState() == IN_PROGRESS) {
			// std::cout << "Found task with in progress" << std::endl;
			// std::cout << "StartTime: " << task.getStartTime() << std::endl;
			// std::cout << "Duration: " << task.getDuration() << std::endl;
			// std::cout << "Current Time: " << time << std::endl;

			if (task.getStartTime() + task.getDuration() == time) {
//				std::cout << "I finished a task! "<< getJobID() << std::endl;
//				std::cout << "TaskID = " << task.getTaskID() << std::endl;
//				std::cout << "with machinenumber: " << task.getMachineNumber()<< std::endl;
				task.finishTask(time);
			}
		}
	}
}

// getJobID:
unsigned short job::getJobID() const {
	return this->jobID;
}

// getTotalJobDuration:

unsigned long long job::getTotalJobDuration() const {
	return this->totalJobDuration;
}

void job::printJobDetails() const {
	std::cout << getJobID() << "\t" << taskList.front().getStartTime() << "\t"
			<< taskList.back().getEndTime() << std::endl;
}

std::ostream& operator<<(std::ostream &os, const job &RHS) {

	os << "| Job ID: ";
	os << RHS.getJobID();
	os << " | Duration: ";
	os << RHS.getTotalJobDuration();
	os << " |";
	os << std::endl;
	return os;
}

bool job::hasActiveTasks() const {
    for (const task &currentTask : taskList) {
        if (currentTask.getCurrentState() == IN_PROGRESS) {
            return true;
        }
    }
    return false;
}

std::vector<task>& job::getTaskList() {
    return this->taskList;
}
