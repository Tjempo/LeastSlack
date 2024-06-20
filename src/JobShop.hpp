#ifndef JobShop_HPP_
#define JobShop_HPP_

typedef unsigned long long int timeType;

#include "Job.hpp"
#include "Config.hpp"
#include "Machine.hpp"

#include <iostream>
#include <vector>

class JobShop
{
private:
    unsigned short amountOfMachines;
    unsigned short amountOfJobs;
    timeType currentTime;

    std::vector<Job> jobs;
    std::vector<Job> completedJobs;
    std::vector<Machine> machines;


public:
    JobShop() = delete;
    JobShop(const Config &Config);

    ~JobShop();

    void initialize(const std::vector<std::vector<unsigned short>> &c);
    void calculateSlack();
    void sortBySlack();
    timeType getLongestJobDuration(); //Should be moved to calculateSlack()
    bool allJobsDone();
    void run();

    void removeFinishedJobs();

    void printJobResults();

    //Getters & Setters:
    unsigned short getAmountOfMachines() const;
	unsigned short getAmountOfJobs() const;
    const std::vector<Job>& getJobs() const;
};

std::ostream& operator <<(std::ostream &os, const JobShop &JobShop);


#endif // JobShop_HPP_