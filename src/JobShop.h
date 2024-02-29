/*
 * JobShop.h
 * Created on: 26 feb. 2024
 * Author: Timo
 */


#ifndef JOBSHOP_H_
#define JOBSHOP_H_

#include "global.h"
#include "job.h"
#include <fstream>
#include <sstream>

class JobShop {
public:
	JobShop(); //Empty construcor
    JobShop(const std::string &filePath);
    JobShop(const JobShop &other); //Copy constructor

    void readFile(const std::string &fileName);

	virtual ~JobShop(); //Destructor

protected:
	std::vector<std::string> jobs; //is nu nog een string moet Job worden

private:
	void readFirstLine(const std::string &fileName);
    void readTasks(const std::string &fileName);

    void schedule();

    unsigned short nAmountOfTasks;
	unsigned short nAmountOfMachines;
};

#endif /* JOBSHOP_H_ */
