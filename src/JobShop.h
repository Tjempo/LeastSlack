#ifndef JOBSHOP_H_
#define JOBSHOP_H_

#include "global.h"
#include <fstream>
#include <sstream>

class JobShop {
public:
	JobShop(); //Empty construcor
	JobShop(const std::string filePath); //Filled constructor
	JobShop(const JobShop &other); //Copy constructor

    void readFile(const std::string fileName);

	virtual ~JobShop(); //Destructor

private:
	short nAmountOfTasks;
	short nAmountOfMachines;

};

#endif /* JOBSHOP_H_ */
