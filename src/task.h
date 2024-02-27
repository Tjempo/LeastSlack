/*
 * task.h
 *
 *  Created on: 26 feb. 2024
 *      Author: roymu
 */

#ifndef TASK_H_
#define TASK_H_

#include "state.h"

class task {
public:
	// constructors + destructor
	task();
	task(unsigned short machineNumber, unsigned short duration);
	task(const task& RHS);
	virtual ~task();
	// operators
	task& operator=(const task& RHS);
	// functions
	// --machineNumber_get_set
	void setMachineNumber(unsigned short machineNumber);
	unsigned short getMachineNumber();
	// --duration_get_set
	void setDuration(unsigned short duration);
	unsigned short getDuration();
	// --finished_get_set
	void setFinished(state state);
	state getCurrentState();
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
	unsigned long startTime;
	unsigned long endTime;
};

#endif /* TASK_H_ */
