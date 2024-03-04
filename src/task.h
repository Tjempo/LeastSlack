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
	task() = delete;
	task(unsigned short ID, unsigned short machineNumber, unsigned short duration);
	task(const task& RHS);
	virtual ~task();
	// operators
	task& operator=(const task& RHS);

	// functions

	void activateTask(unsigned long long time);

	// --taskID_get
	unsigned short getTaskID() const;
	// --machineNumber_get
	unsigned short getMachineNumber() const;
	// --duration_get
	unsigned short getDuration() const;
	// --state_get_set
	void setState(state state);
    state getCurrentState() const;
    // state getCurrentState(); // DEPRECATED
    // -- earliestStartTime_get_set
	void setEarliestStartTime(unsigned long time);
	unsigned long getEarliestStartTime() const;
	// --startTime_get_set
	void setStartTime(unsigned long time);
	unsigned long getStartTime() const;
	// --endTime_get_set
	void setEndTime(unsigned long time);
	unsigned long getEndTime() const ;


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
