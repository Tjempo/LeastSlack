#include "Task.hpp"

//*** Constructor and Destructor ***

Task::Task() : taskId(0), machineNumber(0), duration(0), EST(0), startTime(0), endTime(0) {
}

Task::Task(timeType id, timeType machineNr, timeType dur) : taskId(id), machineNumber(machineNr), duration(dur), EST(0), startTime(0), endTime(0) {

}

//Copy constructor
Task::Task(const Task &RHS) :
	taskId(RHS.taskId), machineNumber(RHS.machineNumber), duration(RHS.duration),EST(RHS.EST), 
	startTime(RHS.startTime), endTime(RHS.endTime) {
}

// Destructor
Task::~Task() {

}


// *** Logic Operators ***:


// Less Than Operator:
bool Task::operator<(const Task &RHS) const {
	return this->taskId < RHS.taskId;
}

// Assignment Operator:
Task& Task::operator=(const Task &RHS) {
	if (this != &RHS) {
		taskId = RHS.taskId;
		machineNumber = RHS.machineNumber;
		duration = RHS.duration;
		EST = RHS.EST;
		startTime = RHS.startTime;
		endTime = RHS.endTime;
	}
	return *this;
}

// Equality Operator:
bool Task::operator ==(const Task &rhs) {
	return this->taskId == rhs.taskId;
}


// *** Getters and Setters ***

timeType Task::getTaskId() const {
	return this->taskId;
}

timeType Task::getTaskDuration() const {
	return this->duration;
}

timeType Task::getMachineNumber() const {
	return this->machineNumber;
}

timeType Task::getEST() const {
	return this->EST;
}

timeType Task::getStartTime() const {
	return this->startTime;
}

timeType Task::getEndTime() const {
	return this->endTime;
}

bool Task::getTaskStarted() const {
	return startTime != endTime;
}

bool Task::getTaskBusy(unsigned short currentTime) const {
	if (!this->getTaskStarted()) {
		return false;
	}
	return currentTime >= startTime && currentTime < endTime;
}

bool Task::getTaskDone(unsigned short currentTime) const {
	if (!this->getTaskStarted()) {
		return false;
	}
	return currentTime >= endTime;
}

void Task::setEST(timeType newEST) {
	this->EST = newEST;
}


//*** Functions: ***

void Task::startTask(unsigned short startTime) {
	this->startTime = startTime;
	this->endTime = startTime + this->duration;
}

//*** Stream Operator: ***

std::ostream& operator<<(std::ostream &os, const Task &t) {
	os << "Task Number: " << t.getTaskId();
	os << " On Machine: " << t.getMachineNumber();
	os << " Duration: " << t.getTaskDuration();
	os << " EST: " << t.getEST();
	os << " Start Time: " << t.getStartTime();
	os << " End Time: " << t.getEndTime() << std::endl;
	return os;
}