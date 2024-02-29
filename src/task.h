/*
 * task.h
 *
 *  Created on: 26 feb. 2024
 *      Author: roymu
 */

#ifndef TASK_H_
#define TASK_H_

#include "state.h"
#include "global.h"
#include <iostream>

class task {
public:
	// constructors + destructor
	task();
	task(unsigned short ID, unsigned short machineNumber, unsigned short duration);
	task(const task& RHS);
	virtual ~task();
	// operators
	task& operator=(const task& RHS);

	// functions
	// --taskID_get
	unsigned short getTaskID();
	// --machineNumber_get
	unsigned short getMachineNumber();
	// --duration_get
	unsigned short getDuration();
	// --state_get_set
	void setState(state state);
	state getCurrentState();
	// -- earliestStartTime_get_set
	void setEarliestStartTime(unsigned long time);
	unsigned long getEarliestStartTime();
	// --startTime_get_set
	void setStartTime(unsigned long time);
	unsigned long getStartTime();
	// --endTime_get_set
	void setEndTime(unsigned long time);
	unsigned long getEndTime();


private:
	unsigned short taskID;
	unsigned short machineNumber;
	unsigned short duration;
	state currentState;
	unsigned long earliestStartTime;
	unsigned long startTime;
	unsigned long endTime;
};

#endif /* TASK_H_ */
