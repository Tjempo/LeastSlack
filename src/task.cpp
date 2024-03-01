/*
 * task.cpp
 *
 *  Created on: 26 feb. 2024
 *      Author: roymu
 */

#include "task.h"

// constructors + destructor
/*
task::task() :
		taskID(0), machineNumber(0), duration(0), currentState(LIMBO), earliestStartTime(
				0), startTime(0), endTime(0) {

}
*/

task::task(unsigned short ID, unsigned short machineNumber, unsigned short duration) : taskID(ID), machineNumber(machineNumber), duration(duration), currentState(NOT_COMPLETED), earliestStartTime(0), startTime(0), endTime(0) {
	std::cout << "Task created: " << ID << ", " << machineNumber << ", " << duration << std::endl;

}

task::task(const task &RHS) :
		taskID(RHS.taskID), machineNumber(RHS.machineNumber), duration(
				RHS.duration), currentState(RHS.currentState), earliestStartTime(
				RHS.earliestStartTime), startTime(RHS.startTime), endTime(
				RHS.endTime) {

}

task::~task() {
	// TODO Auto-generated destructor stub
}
// operators
task& task::operator=(const task &RHS) {
	if(this == &RHS) {
			std::cout << "this the same" << std::endl;
			return *this;
		}
	this->taskID = RHS.taskID;
	this->machineNumber = RHS.machineNumber;
	this->duration = RHS.duration;
	this->currentState = RHS.currentState;
	this->earliestStartTime = RHS.earliestStartTime;
	this->startTime = RHS.startTime;
	this->endTime = RHS.endTime;

	return *this;
}

// functions
// --machineNumber_get
unsigned short task::getMachineNumber() {
	return this->machineNumber;
}

// --duration_get
unsigned short task::getDuration() {
	return this->duration;
}

// --state_get_set
void task::setState(state state) {
	this->currentState = state;
}

state task::getCurrentState() {
	return this->currentState;
}

// -- earliestStartTime_get_set
void task::setEarliestStartTime(unsigned long time) {
	this->earliestStartTime = time;
}
unsigned long task::getEarliestStartTime() {
	return this->earliestStartTime;
}

// --startTime_get_set
void task::setStartTime(unsigned long time) {
	this->startTime = time;
}

unsigned long task::getStartTime() {
	return this->startTime;
}

// --endTime_get_set
void task::setEndTime(unsigned long time) {
	this->endTime = time;
}

unsigned long task::getEndTime() {
	return this->endTime;
}

