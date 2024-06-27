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


//*** Calculations *** //

void Job::calculateEST(timeType &currentTime) {
    // If no tasks are available, return early
    if (!getTasksAvailable()) {
        return;
    }

    // Sort tasks by ID to ensure correct order
    this->sortTasksByID();

    // Loop through tasks and calculate EST for each
    for (Task &task : this->taskList) {
        // If the task is done or started, continue to the next task
        if (task.getTaskState() == DONE || task.getTaskState() == STARTED) {
            continue;
        }

        // If it's the first task or a task with ID 0, set EST to currentTime
        if (&task == &this->taskList.front() || task.getTaskId() == 0) {
            task.setEST(currentTime);
        } else {
            // For other tasks, calculate EST based on the previous task's end time
            Task &previousTask = getPreviousTask(task);
            task.setEST(previousTask.getEndTime());
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

Task& Job::getPreviousTask(const Task &task) {
    auto it = std::find(taskList.begin(), taskList.end(), task);
    if (it != taskList.end() && it != taskList.begin()) {
        return *(std::prev(it));
    }
    return *it;
}

bool Job::isPreviousTaskDone(const Task &currentTask) const {
    int taskId = currentTask.getTaskId();
    if (taskId == 0) {
        return true; // First task, no previous task
    }
    const Task &previousTask = this->taskList[taskId - 1];
    return previousTask.getTaskState() == DONE;
}

void Job::startNextTask(timeType currentTime) {
    if(!getTasksAvailable() && getJobDone()){
        return;
    } 

    Task &nextTask = getNextTask();
    if(nextTask.getTaskState() == STARTED){
        return;
    }else{
        nextTask.startTask(currentTime);
    }
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