#include "task.h"
#include "JobShop.h"

// Constructors + destructor
task::task(unsigned short ID, unsigned short machineNumber, unsigned short duration) :
		taskID(ID), machineNumber(machineNumber), duration(duration), currentState(
				NOT_COMPLETED), earliestStartTime(0), startTime(0), endTime(0) {
}

//Copy constructor
task::task(const task &RHS) :
	taskID(RHS.taskID), machineNumber(RHS.machineNumber), duration(RHS.duration), 
	currentState(RHS.currentState), earliestStartTime(RHS.earliestStartTime), 
	startTime(RHS.startTime), endTime(RHS.endTime) {
	//Niet tot zover
}

task::~task() {
	// Destructor stub
}

// Operator=
task& task::operator=(const task &RHS) {
	if (this != &RHS){
		this->taskID = RHS.taskID;
		this->machineNumber = RHS.machineNumber;
		this->duration = RHS.duration;
		this->currentState = RHS.currentState;
		this->earliestStartTime = RHS.earliestStartTime;
		this->startTime = RHS.startTime;
		this->endTime = RHS.endTime;
	}
	return *this;
}

// Operator<
bool task::operator<(const task &RHS) const {
	return this->taskID == RHS.taskID;
}

// Functions
void task::activateTask(unsigned long long time) {
	// std::cout << "activate task with id" << this->getTaskID() << std::endl;
	this->setState(IN_PROGRESS);
	this->setStartTime(time);
}

void task::finishTask(unsigned long long time) {
	// std::cout << "finish task with id" << this->getTaskID() << std::endl;
	this->setState(COMPLETED);
	this->setEndTime(time);
}

// getTaskID:
unsigned short task::getTaskID() const {
	return this->taskID;
}

// getMachineNumber:
unsigned short task::getMachineNumber() const {
	return this->machineNumber;
}

// getDuration:
unsigned short task::getDuration() const {
	return this->duration;
}

// setState:
void task::setState(state state) {
	this->currentState = state;
}

// getCurrentState:
state task::getCurrentState() const {
	return this->currentState;
}

// setEarliestStartTime:
void task::setEarliestStartTime(unsigned long long time) {
	this->earliestStartTime = time;
}
unsigned long long task::getEarliestStartTime() const {
	return this->earliestStartTime;
}

// setStartTime:
void task::setStartTime(unsigned long long time) {
	this->startTime = time;
}

//getStartTime:
unsigned long long task::getStartTime() const {
	return this->startTime;
}

// setEndTime:
void task::setEndTime(unsigned long long time) {
	this->endTime = time;
}

// getEndTime:
unsigned long long task::getEndTime() const {
	return this->endTime;
}

bool task::getTaskStarted() const{
	if(this->currentState == IN_PROGRESS){
		return true;
	}
	else{
		return false;
	}
}

// Stream Operator:
std::ostream& operator<<(std::ostream &os, const task &RHS) {
	os << "task: " << std::endl;
	os << "| task ID: " << RHS.getTaskID();
	os << " | machineNumber: " << RHS.getMachineNumber();
	os << " | duration: " << RHS.getDuration();
	os << " | currentState: ";
	if (RHS.getCurrentState() == COMPLETED) {
		os << " COMPLETED";
	} else if (RHS.getCurrentState() == NOT_COMPLETED) {
		os << " NOT_COMPLETED";
	} else if (RHS.getCurrentState() == IN_PROGRESS) {
		os << " IN_PROGRESS";
	} else {
		os << "fuck";
	}
	os << " | EST: " << RHS.getEarliestStartTime();
	os << " | ST: " << RHS.getStartTime();
	os << " | ET: " << RHS.getEndTime();
	os << " |";
	os << std::endl;
	return os;
}