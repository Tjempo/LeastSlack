#include "Job.hpp"

//*** Constructors & Destructors ***

Job::Job(unsigned short jobId, const std::vector<unsigned short> &Config) : id(jobId){
    //Reserve memory:
	taskList.reserve(Config.size() / 2);
    //Create tasks from the Config vector:
    for (size_t i = 0; i < Config.size(); ++i) {
        if (i % 2 == 0) {
            taskList.emplace_back(Task(i / 2, Config[i], Config[i + 1]));
            // std::cout << "Task " << i << " = " << Config[i] << ","<< Config[i + 1] << std::endl;
        }
    }
}

Job::~Job(){}

//*** Functions *** //

void Job::sortTasksByID(){
	std::sort(this->taskList.begin(), this->taskList.end());
}


//*** Calculations *** //

void Job::calculateEST(timeType currentTime){
    if (this->getJobsAvailable()){
        sortTasksByID();
        auto nextTaskIter = std::find(taskList.begin(), taskList.end(), getNextTask());
        if (nextTaskIter != taskList.end())
            nextTaskIter->setEST(currentTime);

        for (auto it = nextTaskIter + 1; it != taskList.end(); ++it) {
        // Calculate earliest start time based on dependencies
        it->setEST(calculateEST(*it));
        }
    }
}

//Old function from previous version. Might be broken.
timeType Job::calculateEST(Task &t){
    auto getPreviousTask = [&t](const Task &ts) {
		return ts.getTaskId() == (t.getTaskId() - 1);
	};
	auto previousTaskID = std::find_if(taskList.begin(), taskList.end(),getPreviousTask);
	// If the previous task is not found, it means the current task is the first task

	if (previousTaskID == taskList.end()) {
		// If it is, it can start immediately
		return 0;
	}
	// Calculate EST using predecessor's earliest start time and duration
	return (previousTaskID->getEST() + previousTaskID->getTaskDuration());
}

void Job::calculateTotalJobDuration(){
    sortTasksByID();
	Task lastTask = taskList.back();
	totalDuration = lastTask.getEST() + lastTask.getTaskDuration();
}

void Job::calculateSlack(timeType longestJobDuration) {
	this->slack = longestJobDuration - this->totalDuration;
}


//*** Operators *** //

Job& Job::operator=(const Job &rhs) {
	if (this != &rhs) {
		this->totalDuration = rhs.totalDuration;
		this->id = rhs.id;
		this->slack = rhs.slack;
		this->taskList = rhs.taskList;
	}
	return *this;
}

bool Job::operator<(const Job &rhs) const {
	if (this->slack != rhs.slack) {
		return this->slack < rhs.slack;
	}
	return this->id < rhs.id;
}

//*** Getters *** //

unsigned short Job::getJobId() const{
    return this->id;
}

timeType Job::getJobDuration() const{
    return this->totalDuration;
}

const std::vector<Task>& Job::getTasks() const{
    return this->taskList;
}

bool Job::getJobDone(timeType currentTime){
    for (const Task &t : taskList){
        if(!t.getTaskDone(currentTime)){
            return false;
        }
    }
    return true;
}

bool Job::checkTaskProgress(timeType time){
    for(const Task &t : taskList){
        if(t.getTaskBusy(time)){
            return true;
        }
    }
    return false;
}

bool Job::startNextTask(unsigned short currentTime) {

	if (!this->getJobsAvailable()) {
		return false;
	}
	if (this->getJobDone(currentTime)) {
		return false;
	}
	Task &nextTask = this->getNextTask();
	if (nextTask.getTaskStarted()) {
		return false;
	}
	nextTask.startTask(currentTime);
	return true;
}

/*
Task& Job::getNextTask(){
    sortTasksByID(); //Always do this to avoid problems.

    // Find the first task that has not started
    auto next = std::find_if(taskList.begin(), taskList.end(), [](const Task &t) {
        return !t.getTaskStarted();
    });

    // Return the found task if any, otherwise return the last task using the ternary operator
    return (next != taskList.end()) ? *next : taskList.back();
}
*/


Task& Job::getNextTask() {
	// sort the tasks so I will get the actual first task
	this->sortTasksByID();
	auto taskDone = [](const Task &t) {
		return !t.getTaskStarted();
	};
	auto next = std::find_if(taskList.begin(), taskList.end(), taskDone);
	// if there is a task found that task can be returned
	if (next != taskList.end()) {
		return *next;
	}

	return taskList[taskList.size() - 1];
}


bool Job::getJobsAvailable() {
    for (const Task &currentTask : taskList) {
        if (currentTask.getTaskStarted()) {
            return false;
        }
    }
    return true;
}

//*** Stream Operator: *** //

std::ostream& operator<<(std::ostream &os, const Job &job){
    os << "Job ID:" << job.getJobId();
    os << " Duration: " << job.getJobDuration();

    for(const Task &t : job.getTasks()){
        os << t;
    }

	return os;
}

void Job::printJobDetails() const {
	std::cout << this->getJobId() << "\t" << taskList.front().getStartTime() 
    << "\t" << taskList.back().getEndTime() << std::endl;
}