#include "Job.hpp"

//*** Constructor and Destructor ***

Job::Job(): jobID(0), jobDuration(0), slackTime(0){
    std::cout << "Job created with no args." << std::endl;
}

Job::Job(unsigned short id, const std::vector<unsigned short> &config): jobID(id), jobDuration(0), slackTime(0){
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

void Job::checkTaskProgress(timeType &currentTime){
    for(Task &task : this->taskList){
        if (task.getTaskState() == STARTED && task.getEndTime() <= currentTime) {
            std::cout << "Task " << task.getTaskId() << " on machine " << task.getMachineNumber() << " is done." << std::endl;
            task.setTaskDone();
        }
    }
}


//*** Calculations *** //

void Job::calculateEST(timeType &currentTime){
    if(!getTasksAvailable()){
        return;
    }
    this->sortTasksByID();
    auto& nextTask = this->getNextTask();

    if(nextTask.getTaskState() == DONE || nextTask.getTaskState() == STARTED){
        return;
    }

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
	this->sortTasksByID(); //Might not be needed
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

bool Job::operator>(const Job &rhs) const {
    //Sort by slack time if not equal, else sort by jobID using the ternary operator:
	return (this->slackTime != rhs.slackTime) ? this->slackTime > rhs.slackTime : this->jobID > rhs.jobID;
}


// *** Getters and Setters ***:

unsigned short Job::getJobID() const{
    return this->jobID;
}

timeType Job::getJobDuration() const{
    return this->jobDuration;
}

timeType Job::getSlackTime() const{
    return this->slackTime;
}


const std::vector<Task>& Job::getTaskList() const{
    return this->taskList;
}

//Dit is ook helemaal beun... Anders werkt de stream operator niet
std::vector<Task>& Job::getTaskList(){
    return this->taskList;
}


bool Job::getTasksAvailable(){
    for(const Task &task : this->taskList){
        if(task.getTaskState() == NOT_STARTED){
            return true;
        }
    }
    return false;
}

bool Job::getJobDone(){
    for(const Task &task : this->taskList){
        if(task.getTaskState() != DONE){
            return false;
        }
    }
    return true;
}


bool Job::getJobStarted() const {
    for (const Task &task : this->taskList) {
        if (task.getTaskState() == STARTED) {
            return true;
        }
    }
    return false;
}

Task& Job::getNextTask(){
    this->sortTasksByID(); //Might not be needed
    auto taskDone = [](const Task &t) {
		return t.getTaskState() == NOT_STARTED;
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

bool Job::isPreviousTaskDone(const Task &t) {
    // If the task is the first task, return true
    if(t.getTaskId() == 0){
        return true;
    }

    // Find the task with ID one less than the given task
    auto previousTaskIter = std::find_if(taskList.begin(), taskList.end(), [&t](const Task &task) {
        return task.getTaskId() == t.getTaskId() - 1;
    });

    // If the previous task is not found, return false
    if (previousTaskIter == taskList.end()) {
        return false;
    }

    // Return true if the previous task state is DONE, false otherwise
    return previousTaskIter->getTaskState() == DONE;
}



//*** Stream operator ***//
std::ostream& operator<<(std::ostream &os, const Job &job){ // Change the return type to std::ostream&
    os << "Job ID: " << job.getJobID() << std::endl;
    os << "Job Duration: " << job.getJobDuration() << std::endl;
    os << "Slack Time: " << job.getSlackTime() << std::endl;
    os << "Tasks:" << std::endl;
    for(const Task &task : job.getTaskList()){
        os << task << std::endl;
    }
    return os;
}


void Job::printJobDetails() const {
	std::cout << getJobID() << "\t" << taskList.front().getStartTime() << "\t" << taskList.back().getEndTime() << std::endl;
}