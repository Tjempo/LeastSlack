#include "JobShop.hpp"


//** Constructors & Destructors **//

JobShop::JobShop(const Config &c) : amountOfMachines(c.getAmountOfMachines()), amountOfJobs(c.getAmountOfJobs()), currentTime(0) {
    this->initialize(c.getConfigVector());
}

JobShop::~JobShop(){/*Empty*/}

//** Functions **//

void JobShop::initialize(const std::vector<std::vector<unsigned short>> &Config){
    // Reserve memory for jobs vector to avoid reallocation
    jobs.reserve(Config.size());
    machines.reserve(amountOfMachines);

    //Initialize Jobs:
    unsigned short id = 0;
    for (const auto &job : Config) {
        jobs.emplace_back(Job(id, job));
    }

    //Initialize Machines:
    for (int i = 0; i < amountOfMachines; i++) {
		machines.emplace_back(Machine());
	}
}

void JobShop::run(){
    while(!allJobsDone()){
        removeFinishedJobs();
        calculateSlack();
        sortBySlack();

        for(Job &job : jobs){
            if (job.checkTaskProgress(currentTime)) {
				continue;
			}

			Task &current = job.getNextTask();
			unsigned short machineNr = current.getMachineNumber();
			// if a machine is already busy another task cannot be started
			if (!machines[machineNr].getBusy(currentTime)) {
				job.startNextTask(currentTime); //Todo
				machines[machineNr].startMachine(currentTime, current.getTaskDuration());
                std::cout << current.getTaskDuration() << std::endl;
			}
            job.calculateSlack(getLongestJobDuration());
		}
        currentTime++;
        // std::cout << "Current Time: " << currentTime << std::endl;
        if(currentTime > 200){
            break;
        }
    }
    printJobResults(); //After all jobs are done
}

void JobShop::removeFinishedJobs() {
	for (auto j = jobs.begin(); j < jobs.end();) {
		if (j->getJobDone(currentTime)) {
			completedJobs.push_back(*j);
			j = jobs.erase(j);
		} else {
			++j;
		}
	}
}

void JobShop::calculateSlack(){
    for (Job &job : jobs) {
        if (job.checkTaskProgress(currentTime)) {
            // Get the next task for the job
            auto &currentTask = job.getNextTask();

            // Calculate earliest start times based on machine availability
            if (machines[currentTask.getMachineNumber()].getAvailabeAtTime() > currentTime)
                job.calculateEST(machines[currentTask.getMachineNumber()].getAvailabeAtTime());
            else
                job.calculateEST(currentTime);

            // Calculate duration
            job.calculateTotalJobDuration();

            // Calculate slack for the task
            job.calculateSlack(getLongestJobDuration());
        }
    }
}

timeType JobShop::getLongestJobDuration() {
	auto maxDuration = [](const Job &a, const Job &b) {
		return a.getJobDuration() < b.getJobDuration();
	};
	auto longestTask = std::max_element(jobs.begin(), jobs.end(), maxDuration);
	return longestTask->getJobDuration();
}

bool JobShop::allJobsDone() {
    // std::cout << jobs.size() << std::endl;
	return jobs.size() == 0;
}

void JobShop::sortBySlack(){
    std::sort(jobs.begin(), jobs.end());
}

void JobShop::printJobResults() {
	std::cout << "call: printJobResults()" << std::endl;
	std::sort(jobs.begin(), jobs.end(), [](const Job &job1, const Job &job2) {
		return job1.getJobId() < job2.getJobId();
	});
	for (Job &job : jobs) {
		job.printJobDetails();
	}
}

//** Getters & Setters **//

unsigned short JobShop::getAmountOfMachines() const{
    return this->amountOfMachines;
}

unsigned short JobShop::getAmountOfJobs() const{
    return this->amountOfJobs;
}

const std::vector<Job>& JobShop::getJobs() const{
    return this->jobs;
}

//** Stream Operators **//

std::ostream& operator <<(std::ostream &os, const JobShop &JobShop) {
	os << "Amount of Jobs: " << JobShop.getAmountOfJobs() << std::endl;
    os << "Amount of Machines: " << JobShop.getAmountOfMachines() << std::endl;

	for (const Job &job : JobShop.getJobs()) {
		os << job;
	}
	return os;
}