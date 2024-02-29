/*
 * state.h
 *
 *  Created on: 27 feb. 2024
 *      Author: roymu
 */

#ifndef STATE_H_
#define STATE_H_

enum state {
	NOT_COMPLETED,
	IN_PROGRESS,
	COMPLETED,
	LIMBO, // for if a task was initialized without proper parameters
};



#endif /* STATE_H_ */
