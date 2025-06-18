#include "JobShop.hpp"
#include <numeric>  // For std::iota

//*** Constructors & Destructor ***//

JobShop::JobShop(const Config &conf) : amountOfMachines(conf.getAmountOfMachines()), amountOfJobs(conf.getAmountOfJobs()), currentTime(0) {
    this->initialize(conf.getConfigVector());
    this->machineInUseUntil.resize(amountOfMachines, 0);  // Resize the vector to the required size and initialize all elements to 0
}

JobShop::~JobShop(){}  // Now I am become Destructor, the destroyer of Jobshop.

//*** Functions ***//
void JobShop::initialize(const std::vector<std::vector<unsigned short>> &config) {
    this->jobList.reserve(config.size());  // Avoid reallocations
    unsigned short id = 0;
    for (const auto &job : config) {
        this->jobList.emplace_back(id, job);
        ++id;
    }
}


void JobShop::checkJobProgress() {
    for (Job &job : this->jobList) {
        job.checkTaskProgress(this->currentTime);
    }
}

//*** Scheduling ***//

void JobShop::run() {
    while (!this->allJobsDone()) {
        this->checkJobProgress();  // Check and update task states
        this->calculateSlackTime();
        this->sortJobs();

        for (Job &job : this->jobList) {
            if (!job.getTasksAvailable() || !job.isPreviousTaskDone(job.getNextTask())) {
                continue;  // Skip if no tasks available or previous task is not done
            }

            Task &currentTask = job.getNextTask();

            if (currentTask.getEST() <= currentTime) {
                if (this->machineInUseUntil[currentTask.getMachineNumber()] <= currentTime) { //Dont use .at() here, it is slower and we know the index is valid.
                    currentTask.startTask(currentTime);
                    this->machineInUseUntil[currentTask.getMachineNumber()] = currentTime + currentTask.getTaskDuration();
                }
            }
        }
        // Update the currentTime:
        ++this->currentTime;
    }
    this->printResults();
}

//*** Calculations: ***//

void JobShop::calculateSlackTime() {
    for (Job &job : this->jobList) {
        if (!job.getTasksAvailable())
            continue;
        const Task &current = job.getNextTask();
        unsigned short machineNr = current.getMachineNumber();

        if (machineInUseUntil.at(machineNr) > currentTime) {
            job.calculateEST(machineInUseUntil.at(machineNr));
        } else {
            job.calculateEST(currentTime);
        }
        job.calculateJobDuration();
    }

    timeType longestJobDuration = this->getLongestJobDuration();
    // This is split into two loops to ensure that all jobs have their jobDuration calculated before calculating slack time.
    for (Job &job : this->jobList) {
        job.calculateSlackTime(longestJobDuration);
    }
}

//*** Sorting ***//

void JobShop::sortJobs() {
    // Create a vector of indices to jobList
    std::vector<size_t> indices(this->jobList.size());
    std::iota(indices.begin(), indices.end(), 0);

    std::sort(indices.begin(), indices.end(), [this](size_t i1, size_t i2) {
        timeType _j1SlackTime = this->jobList[i1].getSlackTime();
        timeType _j2SlackTime = this->jobList[i2].getSlackTime();

        if (_j1SlackTime == _j2SlackTime) {
            return this->jobList[i1].getJobID() < this->jobList[i2].getJobID();
        }
        return _j1SlackTime < _j2SlackTime;
    });

    // Rebuild jobList based on sorted indices
    std::vector<Job> sortedJobs;
    sortedJobs.reserve(this->jobList.size());
    for (size_t index : indices) {
        sortedJobs.emplace_back(std::move(this->jobList[index]));
    }
    this->jobList = std::move(sortedJobs);
}



//*** Getters & Setters ***//

bool JobShop::allJobsDone() const {
    return std::all_of(this->jobList.begin(), this->jobList.end(),
        [](const Job &job) { return job.getJobDone(); });
}

timeType JobShop::getLongestJobDuration() {
    auto maxDuration = [](const Job &LHS, const Job &RHS) {
        return LHS.getJobDuration() < RHS.getJobDuration();
    };
    auto longestTask = std::max_element(jobList.begin(), jobList.end(), maxDuration);
    return longestTask->getJobDuration();
}

//*** Stream operator (kinda) ***//

void JobShop::printResults() {
    std::sort(jobList.begin(), jobList.end(), [](const Job &job1, const Job &job2) {
        return job1.getJobID() < job2.getJobID();
    });
    for (Job const &job : jobList) {
        job.printJobDetails();
    }
}
