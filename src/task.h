/*
 * task.h
 *
 *  Created on: 26 feb. 2024
 *      Author: roymu
 */

#ifndef TASK_H_
#define TASK_H_

#include <iostream>
#include "state.hpp"

class JobShop;

class task {
public:
	// constructors + destructor
	task() = delete;
	task(unsigned short ID, unsigned short machineNumber, unsigned short duration);
	task(const task& RHS);
	virtual ~task();
	// operators
	task& operator=(const task& RHS);

	// Functions

	void activateTask(unsigned long long time);
	void finishTask(unsigned long long time);

	// Getters:
	unsigned short getTaskID() const;
	unsigned short getMachineNumber() const;
	unsigned short getDuration() const;
	unsigned long getStartTime() const;
	unsigned long getEndTime() const ;
	unsigned long getEarliestStartTime() const;
	state getCurrentState() const;

	// Setters:
	void setEarliestStartTime(unsigned long time);
	void setState(state state);
	void setStartTime(unsigned long time);
	void setEndTime(unsigned long time);



private:
	unsigned short taskID;
	unsigned short machineNumber;
	unsigned short duration;
	state currentState;
	unsigned long earliestStartTime;
	unsigned long startTime;
	unsigned long endTime;
};

std::ostream& operator<<(std::ostream& os, const task& RHS);

#endif /* TASK_H_ */
