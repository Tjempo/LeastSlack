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


    //*** Stream ***//
    void printResults();

private:
    //*** Variables ***//
    unsigned short amountOfMachines;
    unsigned short amountOfJobs;
    std::vector<Job> jobList;


    //*** Functions ***//
    void initialize(const std::vector<std::vector<unsigned short>> &config);
};

#endif // JOBSHOP_HPP
