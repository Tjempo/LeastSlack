#include "Task.hpp"

//*** Constructor and Destructor ***

Task::Task() : taskId(0), machineNumber(0), duration(0), EST(0), startTime(0), endTime(0) {
}

Task::Task(timeUnit id, timeUnit machineNr, timeUnit dur) : taskId(id), machineNumber(machineNr), duration(dur), EST(0), startTime(0), endTime(0) {

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

timeUnit Task::getTaskId() const {
	return this->taskId;
}

timeUnit Task::getDuration() const {
	return this->duration;
}

timeUnit Task::getMachineNumber() const {
	return this->machineNumber;
}

timeUnit Task::getEST() const {
	return this->EST;
}

timeUnit Task::getStartTime() const {
	return this->startTime;
}

timeUnit Task::getEndTime() const {
	return this->endTime;
}



//*** Stream Operator: ***

std::ostream& operator <<(std::ostream &os, const Task &t) {
	os << "Task Number: " << t.getTaskId();
	os << " On Machine: " << t.getMachineNumber();
	os << " Duration: " << t.getDuration();
	os << " EST: " << t.getEST();
	os << " Start Time: " << t.getStartTime();
	os << " End Time: " << t.getEndTime() << std::endl;
	return os;
}