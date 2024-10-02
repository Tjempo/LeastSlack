#ifndef JOBSHOP_HPP
#define JOBSHOP_HPP

#include <iostream>
#include <vector>

#include "Config.hpp"
#include "Job.hpp"

class JobShop {
   public:
    JobShop(/* no args */) = delete;
    JobShop(const JobShop &other) = delete;  // Copy constructor
    explicit JobShop(const Config &conf);
    ~JobShop();

    //*** Scheduling ***//
    void run();

    //*** Getters ***//
    bool allJobsDone() const;
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

    //*** Calculations ***//
    void calculateSlackTime();

    //*** Sorting ***//

    /// @brief Sorts the jobs by slack time. If the slack time is equal, the job with the longest duration will be first.
    void sortJobs();

    //*** Functions ***//
    void initialize(const std::vector<std::vector<unsigned short>> &config);
    void checkJobProgress();
};

#endif  // JOBSHOP_HPP
