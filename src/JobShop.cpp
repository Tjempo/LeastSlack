#include "JobShop.hpp"

//*** Constructors & Destructor ***//

JobShop::JobShop(const Config &conf): amountOfMachines(conf.getAmountOfMachines()), amountOfJobs(conf.getAmountOfJobs()), currentTime(0){
    std::cout << "JobShop created with " << this->amountOfMachines << " machines and " << this->amountOfJobs << " jobs." << std::endl;
    this->initialize(conf.getConfigVector());
    this->machineInUseUntil.resize(amountOfMachines, 0); // Resize the vector to the required size and initialize all elements to 0


}

JobShop::JobShop(unsigned short machines, unsigned short jobs, const std::vector<Job> &jobsList): amountOfMachines(machines), amountOfJobs(jobs), currentTime(0){
    std::cout << "JobShop created with " << amountOfMachines << " machines and " << amountOfJobs << " jobs." << std::endl;
    //Print the jobs:
    for(auto &job : jobsList){
        std::cout << job << std::endl;
    }
    this->machineInUseUntil.resize(amountOfMachines, 0); // Resize the vector to the required size and initialize all elements to 0

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

void JobShop::checkJobProgress() {
    for (Job &job : this->jobList) {
        for (Task &task : job.getTaskList()) {
            if (task.getTaskState() == STARTED && task.getEndTime() <= this->currentTime) {
                task.setTaskDone(); // Mark the task as done when end time is reached
                std::cout << "Task: " << task.getTaskId() << " of Job: " << job.getJobID() << " is done at time " << this->currentTime << std::endl;
            }
        }
    }
}


//*** Scheduling ***//

//please work...
void JobShop::run() {
    while (!this->allJobsDone()) {
        this->checkJobProgress(); // Check and update task states
        this->calculateSlackTime();
        this->sortJobsBySlack();

        for (Job &job : this->jobList) {
            if (!job.getJobStarted()) {
                continue;
            }

            Task &currentTask = job.getNextTask();
            if (!job.isPreviousTaskDone(currentTask)) {
                std::cout << "Previous task for Job " << job.getJobID() << " Task " << currentTask.getTaskId() << " is not done." << std::endl;
                continue; // Skip if previous task is not done
            }

            std::cout << "CurrentTime: " << this->currentTime << " Checking Task: " << currentTask.getTaskId() << " of Job: " << job.getJobID() << std::endl;

            if (currentTask.getEST() <= currentTime) {
                if (this->machineInUseUntil[currentTask.getMachineNumber()] <= currentTime) {
                    // Start task
                    std::cout << "Starting Task: " << currentTask.getTaskId() 
                              << " of Job: " << job.getJobID() 
                              << " on Machine: " << currentTask.getMachineNumber() << std::endl;
                    currentTask.startTask(currentTime);
                    this->machineInUseUntil[currentTask.getMachineNumber()] = currentTime + currentTask.getTaskDuration();
                } else {
                    std::cout << "Machine " << currentTask.getMachineNumber() 
                              << " is in use until " << this->machineInUseUntil[currentTask.getMachineNumber()] << std::endl;
                }
            } else {
                std::cout << "Task " << currentTask.getTaskId() 
                          << " of Job " << job.getJobID() 
                          << " EST " << currentTask.getEST() 
                          << " is greater than current time " << this->currentTime << std::endl;
            }
        }

        ++this->currentTime; // Update the currentTime

        // Debugging output
        std::cout << "CurrentTime: " << this->currentTime << std::endl;
        for (const Job &job : this->jobList) {
            std::cout << job << std::endl;
        }
    }
}



//*** Calculations: ***//


void JobShop::calculateSlackTime() {
    for (Job &job : this->jobList) {
        if (job.getJobStarted()) {
            continue; // Skip if the job has already started
        }

        Task &nextTask = job.getNextTask();
        unsigned short machineNr = nextTask.getMachineNumber();

        // Calculate EST based on machine availability
        if (machineInUseUntil[machineNr] > this->currentTime) {
            job.calculateEST(machineInUseUntil[machineNr]);
        } else {
            job.calculateEST(currentTime);
        }

        // Calculate Job Duration and Slack Time
        job.calculateJobDuration();
        job.calculateSlackTime(this->currentTime);
    }
}


// void JobShop::calculateSlackTime(){
// 	for (Job &j : this->jobList) {
// 		if (!j.getTasksAvailable())
// 			continue;
// 		Task &current = j.getNextTask();

// 		unsigned short machineNr = current.getMachineNumber();
// 		// tasks that use an already busy machine cannot be executed until it is free
//         std::cout << "MachineNr: " << machineNr << " In use until " << machineInUseUntil[machineNr] << std::endl;
// 		if (machineInUseUntil[machineNr] > currentTime){
// 			j.calculateEST(machineInUseUntil[machineNr]);
// 		} else {
// 			j.calculateEST(currentTime);
// 		}
// 		j.calculateJobDuration();
// 	}
// 	// making seperate variable so it isn't calcuted for every job
// 	unsigned short longestJobDuration = this->getLongestJobDuration();
// 	for (Job &j : this->jobList) {
// 		j.calculateSlackTime(longestJobDuration);
// 	}
// }



// void JobShop::calculateSlackTime(){
//     for (Job &j : this->jobList) {
//         Task &currentTask = j.getNextTask();
//         if (!j.getTasksAvailable() || !j.isPreviousTaskDone(currentTask))
//             continue; // Skip this job if no tasks are available or the previous task isn't done

//         unsigned short machineNr = currentTask.getMachineNumber();

//         // Check if the machine is in use and adjust the EST accordingly
//         if (machineInUseUntil[machineNr] > currentTime){
//             j.calculateEST(machineInUseUntil[machineNr]);
//         } else {
//             j.calculateEST(currentTime);
//         }

//         j.calculateJobDuration();
//     }

//     // Calculate slack time as before
//     timeType longestJobDuration = this->getLongestJobDuration();
//     for (Job &j : this->jobList) {
//         j.calculateSlackTime(longestJobDuration);
//     }
// }



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
