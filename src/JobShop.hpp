#ifndef JOBSHOP_HPP
#define JOBSHOP_HPP

#include <iostream>
#include <vector>

#include "Config.hpp"
#include "Job.hpp"

class JobShop{
public:
    JobShop(/* no args */) = delete;
    JobShop(const Config &conf);
    JobShop(unsigned short machines, unsigned short jobs, const std::vector<Job> &jobsList);
    ~JobShop();

    //*** Functions ***//
    void run();

    //*** Calculations ***//
    void calculateSlackTime();


    //*** Scheduling ***//


    //*** Sorting ***//

    /// @brief Sorts the jobs by slack time. If the slack time is equal, the job with the longest duration will be first.
    void sortJobsBySlack();
    

    //*** Getters ***//
    bool allJobsDone();
    timeType getLongestJobDuration();

    //*** Stream ***//
    void printResults();

private:
    //*** Variables ***//
    unsigned short amountOfMachines;
    unsigned short amountOfJobs;
    std::vector<Job> jobList;

    std::vector<timeType> machineInUseUntil;

    timeType currentTime;

    //*** Functions ***//
    void initialize(const std::vector<std::vector<unsigned short>> &config);
};

#endif // JOBSHOP_HPP
