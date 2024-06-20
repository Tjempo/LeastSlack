#include "Job.hpp"

//*** Constructor and Destructor ***

Job::Job(): jobID(0), jobDuration(0), slackTime(0){
    std::cout << "Job created with no args." << std::endl;
}

Job::Job(unsigned short id, const std::vector<unsigned short> &config): jobID(id), jobDuration(0), slackTime(0){
    std::cout << "Job created with args." << std::endl;
    for(unsigned short i = 0; i < config.size(); i+=2){
        taskList.push_back(Task(i / 2, config[i], config[i + 1]));
    }
}

Job::~Job(){
}


// *** Functions ***:
void Job::sortTasksByID(){
	std::sort(this->taskList.begin(), this->taskList.end());
}


//*** Calculations *** //

void Job::calculateEST(timeType &currentTime){
    if(!getTasksAvailable()){
        return;
    }
    this->sortTasksByID();
    auto& nextTask = this->getNextTask();

    auto next = std::find(taskList.begin(), taskList.end(), nextTask);
	if (next == taskList.end()){
		return;
    }

    for (auto it = next; it != taskList.end(); it++){
        if(it == next || it->getTaskId() == 0){
            it->setEST(currentTime); 
        }else{
            it->setEST(calculateEST(*it));
        }
    }
}

timeType Job::calculateEST(const Task &t) {
	auto getPreviousTask = [&t](const Task &ts) {
		return ts.getTaskId() == (t.getTaskId() - 1);
	};
	// If the previous task is not found, it means the current task is the first task
	auto previousTaskID = std::find_if(taskList.begin(), taskList.end(),getPreviousTask);
	if (previousTaskID == taskList.end()) {
		// If it is, it can start immediately, so return 0:
		return 0;
	}
	return (previousTaskID->getEST() + previousTaskID->getTaskDuration()); //else
}


void Job::calculateJobDuration() {
	this->sortTasksByID();
	Task lastTask = taskList.back();
	this->jobDuration = lastTask.getTaskDuration() + lastTask.getEST();
}

void Job::calculateSlackTime(timeType duration){
    this->slackTime = duration - this->jobDuration;
}



// *** Logic Operators ***:

Job& Job::operator=(const Job &rhs) {
	if (this != &rhs) {
		this->jobID = rhs.jobID;
        this->jobDuration = rhs.jobDuration;
        this->slackTime = rhs.slackTime;
        this->taskList = rhs.taskList;
	}
	return *this;
}

bool Job::operator<(const Job &rhs) const {
    //Sort by slack time if not equal, else sort by jobID using the ternary operator:
	return (this->slackTime != rhs.slackTime) ? this->slackTime < rhs.slackTime : this->jobID < rhs.jobID;
}


// *** Getters and Setters ***:

bool Job::getTasksAvailable(){
    for(const Task &task : this->taskList){
        if(task.getTaskState() == NOT_STARTED){
            return true;
        }
    }
    return false;
}

bool Job::getJobDone(timeType &currentTime){
    for(const Task &task : this->taskList){
        if(task.getTaskState() != DONE){
            return false;
        }
    }
    return true;
}

Task& Job::getNextTask(){
    this->sortTasksByID(); //Might not be needed
    auto taskDone = [](const Task &t) {
		return !t.getTaskStarted();
	};
	auto next = std::find_if(taskList.begin(), taskList.end(), taskDone);
	// if there is a task found that task can be returned
	if (next != taskList.end()) {
		return *next;
	}
    else {
        std::cout << "No task found." << std::endl;
        // return *taskList.end(); //This leads to undefined behavior
        return taskList.back();
    }
}

// Might need this if there are problems with getting the next task
/*
std::optional<Task> Job::getNextTask(){
    this->sortTasksByID();
    auto taskDone = [](const Task &t) {
        return !t.getTaskStarted();
    };
    auto next = std::find_if(taskList.begin(), taskList.end(), taskDone);
    // if there is a task found that task can be returned
    if (next != taskList.end()) {
        return *next;
    }
    else {
        return std::nullopt;
    }
}
*/