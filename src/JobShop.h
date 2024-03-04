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
	JobShop() = delete; //Empty construcor
    JobShop(const std::string &filePath);
    JobShop(const JobShop &other); //Copy constructor

    void readFile(const std::string &fileName);

	virtual ~JobShop(); //Destructor

    const std::vector<job> getJobs() const; //Mocht dit nodig zijn:
    unsigned short getAmountOfTasks() const;
    unsigned short getAmountOfMachines() const;
    void schedule();

protected:
	

private:
	void readFirstLine(const std::string &fileName);
    void readTasks(const std::string &fileName);

    void calculateLeastSlack(unsigned long long &time);
    void calculateSlack(unsigned long long &time);

    bool allJobsDone();

    void orderJobsByTotalDuration(std::vector<job>& jobs) const;
    void sortTasks();

    std::vector<bool> machineState;
    std::vector<job> jobs;
    unsigned long long time;
    unsigned short nAmountOfTasks;
	unsigned short nAmountOfMachines;
};

#endif /* JOBSHOP_H_ */
