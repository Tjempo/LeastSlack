#include "JobShop.hpp"

//*** Constructors & Destructor ***//

JobShop::JobShop(const Config &conf): amountOfMachines(conf.getAmountOfMachines()), amountOfJobs(conf.getAmountOfJobs()), currentTime(0){
    std::cout << "JobShop created with " << this->amountOfMachines << " machines and " << this->amountOfJobs << " jobs." << std::endl;
    this->initialize(conf.getConfigVector());
    this->machineInUseUntil.reserve(amountOfMachines); //Reserve memory for the machinesInUseUntil vector

}

JobShop::JobShop(unsigned short machines, unsigned short jobs, const std::vector<Job> &jobsList): amountOfMachines(machines), amountOfJobs(jobs), currentTime(0){
    std::cout << "JobShop created with " << amountOfMachines << " machines and " << amountOfJobs << " jobs." << std::endl;
    //Print the jobs:
    for(auto &job : jobsList){
        std::cout << job << std::endl;
    }
    this->machineInUseUntil.reserve(amountOfMachines); //Reserve memory for the machinesInUseUntil vector: 
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

//*** Scheduling ***//

//please work...
void JobShop::run(){
    //Print the jobs:
    this->calculateSlackTime();

    for(Job &job : this->jobList){
        // job.calculateEST(currentTime); // <--- Belangrijk om te doen voor calculateJobDuration
        // job.calculateJobDuration();
        std::cout << job << std::endl;
    }

    
    //sortJobsBySlack();

    /* while (!this->allJobsDone()){
        for(Job &job : this->jobList){
            const Task &currentTask = job.getNextTask();
            if(currentTask.getEST() <= currentTime){
                //Check if the machine is available:
                if(this->machineInUseUntil[currentTask.getMachineNumber()] <= currentTime){
                    //Start the task:
                    currentTask.startTask(currentTime);
                    //Update the machineInUseUntil vector:
                    this->machineInUseUntil[currentTask.getMachineNumber()] = currentTask.getEndTime();
                }
            }
        }
    }
    */
    
    //printResults();
}



//*** Calculations: ***//

void JobShop::calculateSlackTime(){
    for(Job &job : this->jobList){
        Task &currentTask = job.getNextTask();
        unsigned short machineNumber = currentTask.getMachineNumber();
        if(machineInUseUntil[machineNumber] <= this->currentTime){
            job.calculateEST(machineInUseUntil[machineNumber]);
        }else{
            job.calculateEST(this->currentTime);
        }
        job.calculateJobDuration();
        job.calculateSlackTime(this->getLongestJobDuration());
    }
}

//*** Sorting ***//

void JobShop::sortJobsBySlack(){
    std::sort(this->jobList.begin(), this->jobList.end(), [](const Job &job1, const Job &job2){
        if (job1.getSlackTime() == job2.getSlackTime()) {
            //Sort by jobID if slack time is equal.
            return job1.getJobID() < job2.getJobID(); 
        }
        return job1.getSlackTime() < job2.getSlackTime();
    });
}



//*** Getters & Setters ***//

bool JobShop::allJobsDone() {
	for (Job &job : this->jobList) {
		if (!job.getJobDone()) {
			return false; // When a job is not completed, return false.
		}
	}
	return true;
}

timeType JobShop::getLongestJobDuration() {
    auto maxDuration = [](const Job &LHS, const Job &RHS) {
		return LHS.getJobDuration() < RHS.getJobDuration();
	};
	auto longestTask = std::max_element(jobList.begin(), jobList.end(), maxDuration);
	return longestTask->getJobDuration();
}


//*** Stream operator ***//

void JobShop::printResults(){
    //std::cout << "call: printJobResults()" << std::endl;
	std::sort(jobList.begin(), jobList.end(), [](const Job &job1, const Job &job2) {
		return job1.getJobID() < job2.getJobID();
	});
	for (Job &job : jobList) {
		job.printJobDetails();
	}
}
