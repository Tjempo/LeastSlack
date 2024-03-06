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
		std::cout << "TaskID: " << taskID << std::endl;
		std::cout << "MachineID: " << machineID << " Duration: " << duration
				<< std::endl;
	}
}

job::job(const job &RHS) :
		jobID(RHS.jobID)/*, taskList(RHS.taskList)*/, totalJobDuration(
				RHS.totalJobDuration) {
	for (task task : RHS.taskList) {
		this->taskList.push_back(task);
	}
}

job::~job() {
	// Destructor stub
}

// Operators:

job& job::operator=(const job &RHS) {
	std::cout << "-------job::operator=------" << std::endl;
	std::cout << RHS << std::endl;
	if (this == &RHS) {
		std::cout << "this the same" << std::endl;
		return *this;
	} else {
		this->jobID = RHS.getJobID();
		this->totalJobDuration = RHS.getTotalJobDuration();
		this->taskList = RHS.taskList;
		return *this;
	}
}

bool job::operator<(const job &RHS) const {
	if (this->getTotalJobDuration() < RHS.getTotalJobDuration()) {
		return true;
	} else {
		return false;
	}
}

bool job::operator>(const job &RHS) const {
	if (this->getTotalJobDuration() > RHS.getTotalJobDuration()) {
		return true;
	} else {
		return false;
	}
}

// Functions

void job::calculateEST(unsigned long long time) {
	if (getJobsAvailable()) {
		// Sort taskList by task ID for efficient predecessor search
		std::sort(taskList.begin(), taskList.end(),
				[this](const task &task1, const task &task2) {
					return compareTasksByID(task1, task2);
				});

		// Loop through tasks and calculate EST
		for (size_t i = 0; i < taskList.size(); ++i) {
			// Get the current task reference
			task &currentTask = taskList[i];

			// Calculate and set EST for the current task
			unsigned long long EST = calculateEST(currentTask) + time;
			std::cout << "EST for task " << currentTask.getTaskID() << " is "
					<< EST << std::endl;
			currentTask.setEarliestStartTime(EST);
		}
	} else {
		std::cout << "No more jobs available" << std::endl;
	}
}

unsigned long long job::calculateEST(const task &t) {
	auto getPreviousTask = [&t](const task &ts) {
		return ts.getTaskID() == (t.getTaskID() - 1);
	};

	// Find the previous task
	auto previousTaskID = std::find_if(taskList.begin(), taskList.end(),
			getPreviousTask);
	// If the previous task is not found, it means the current task is the first task

	if (previousTaskID == taskList.end()) {
		// If it is, it can start immediately
		return 0;
	}
	// Calculate EST using predecessor's earliest start time and duration
	return (previousTaskID->getEarliestStartTime()
			+ previousTaskID->getDuration());
}

//Compare tasks by taskID

bool job::compareTasksByID(const task &task1, const task &task2) {
	return task1.getTaskID() < task2.getTaskID();
}

//Calculate Duration:

void job::calculateTotalDuration() {
	unsigned long long totalDuration = 0;

	for (const task &currentTask : taskList) {
		totalDuration += currentTask.getDuration();
	}

	this->totalJobDuration = totalDuration;
	std::cout << "Total Duration of Job " << this->jobID << ": "
			<< totalDuration << std::endl;
}

bool job::isJobDone() {
	for (task &currentTask : taskList) {
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

task job::getTask(unsigned short index) {

	return this->taskList.at(index);
}

task& job::getNextTask() {
	//std::cout << "job::getNextTask - begin" << std::endl;
	for (unsigned short i = 0; i < taskList.size(); ++i) {
		if (taskList[i].getCurrentState() != COMPLETED) {
			//std::cout << "job::getNextTask - end" << std::endl;
			return taskList[i];
		}
	}
	//std::cout << "job::getNextTask - end" << std::endl;
	return taskList.back();
}

void job::checkTaskProgress(unsigned long long time) {
	for (task &task : taskList) {
		if (task.getCurrentState() == IN_PROGRESS) {
			if (task.getStartTime() + task.getDuration() == time) {
				std::cout << "finish a task from job with number: "
						<< getJobID() << std::endl;
				std::cout << "with machinenumber: " << task.getMachineNumber()
						<< std::endl;
				task.finishTask(time);
			}
		}
	}
}

// getJobID:
const unsigned short job::getJobID() const {
	return this->jobID;
}

// getTotalJobDuration:

const unsigned long long job::getTotalJobDuration() const {
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

