#include "JobShop.hpp"

//*** Constructors & Destructor ***//

JobShop::JobShop(const Config &conf): amountOfMachines(conf.getAmountOfMachines()), amountOfJobs(conf.getAmountOfJobs()){
    std::cout << "JobShop created with " << this->amountOfMachines << " machines and " << this->amountOfJobs << " jobs." << std::endl;
    this->initialize(conf.getConfigVector());
}

JobShop::JobShop(unsigned short machines, unsigned short jobs, const std::vector<Job> &jobsList): amountOfMachines(machines), amountOfJobs(jobs){
    std::cout << "JobShop created with " << amountOfMachines << " machines and " << amountOfJobs << " jobs." << std::endl;
    //Print the jobs:
    for(auto &job : jobsList){
        std::cout << job << std::endl;
    }
}

JobShop::~JobShop(){} //Now I am become Destructor, the destroyer of Jobshop.


//*** Functions ***//
void JobShop::initialize(const std::vector<std::vector<unsigned short>> &config){
	unsigned short id = 0;
	for (const std::vector<unsigned short> &job : config) {
		this->jobList.emplace_back(Job(id, job));
		++id;
	}
}

//please work...
void JobShop::run(){
    //Print the jobs:
    timeType currentTime = 0;
    for(Job &job : this->jobList){
        job.calculateEST(currentTime); // <--- Belangrijk om te doen voor calculateJobDuration
        job.calculateJobDuration();

        std::cout << job << std::endl;
    }
}



//*** Operators ***//



//*** Getters & Setters ***//


//*** Steam operator ***//

void JobShop::printResults(){
    //std::cout << "call: printJobResults()" << std::endl;
	std::sort(jobList.begin(), jobList.end(), [](const Job &job1, const Job &job2) {
		return job1.getJobID() < job2.getJobID();
	});
	for (Job &job : jobList) {
		job.printJobDetails();
	}
}
