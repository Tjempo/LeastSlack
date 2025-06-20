#include "Job.hpp"

//*** Constructor and Destructor ***

Job::Job() : jobID(0), jobDuration(0), slackTime(0) {
    // Job created with no args
}

Job::Job(unsigned short id, const std::vector<unsigned short> &config) : jobID(id), jobDuration(0), slackTime(0) {
    for (unsigned short i = 0; i < config.size(); i += 2) {
        taskList.emplace_back(Task(i / 2, config.at(i), config.at(i + 1)));
    }
}

Job::~Job() {
}

// *** Functions ***:
void Job::sortTasksByID() {
    std::sort(this->taskList.begin(), this->taskList.end(), [](const Task &a, const Task &b) {
        return a.getTaskId() < b.getTaskId();
    });
}

void Job::checkTaskProgress(const timeType &currentTime) {
    for (Task &task : this->taskList) {
        if (task.getTaskState() == STARTED && task.getEndTime() <= currentTime) {
            task.setTaskDone();
        }
    }
}

//*** Calculations *** //

void Job::calculateEST(timeType &currentTime) {
    if (!getTasksAvailable()) {
        return;
    }
    this->sortTasksByID();
    auto &nextTask = this->getNextTask();

    if (nextTask.getTaskState() == DONE || nextTask.getTaskState() == STARTED) {
        return;
    }

    auto next = std::find(taskList.begin(), taskList.end(), nextTask);
    if (next == taskList.end()) {
        return;
    }

    for (auto it = next; it != taskList.end(); it++) {
        if (it == next || it->getTaskId() == 0) {
            it->setEST(currentTime);
        } else {
            it->setEST(calculateEST(*it));
        }
    }
}

timeType Job::calculateEST(const Task &t) {
    auto getPreviousTask = [&t](const Task &ts) {
        return ts.getTaskId() == (t.getTaskId() - 1);
    };
    // If the previous task is not found, it means the current task is the first task
    auto previousTaskID = std::find_if(taskList.begin(), taskList.end(), getPreviousTask);
    if (previousTaskID == taskList.end()) {
        // If it is, it can start immediately, so return 0:
        return 0;
    }
    return (previousTaskID->getEST() + previousTaskID->getTaskDuration());  // else
}

void Job::calculateJobDuration() {
    Task lastTask = taskList.back();
    this->jobDuration = lastTask.getTaskDuration() + lastTask.getEST();
}

void Job::calculateSlackTime(timeType duration) {
    this->slackTime = duration - this->jobDuration;
}

// *** Logic Operators ***:

Job &Job::operator=(const Job &RHS) {
    if (this != &RHS) {
        this->jobID = RHS.jobID;
        this->jobDuration = RHS.jobDuration;
        this->slackTime = RHS.slackTime;
        this->taskList = RHS.taskList;
    }
    return *this;
}

bool Job::operator<(const Job &RHS) const {
    // Sort by slack time if not equal, else sort by jobID using the ternary operator:
    return (this->slackTime != RHS.slackTime) ? this->slackTime < RHS.slackTime : this->jobID < RHS.jobID;
}

bool Job::operator>(const Job &RHS) const {
    // Sort by slack time if not equal, else sort by jobID using the ternary operator:
    return (this->slackTime != RHS.slackTime) ? this->slackTime > RHS.slackTime : this->jobID > RHS.jobID;
}

// *** Getters and Setters ***:

unsigned short Job::getJobID() const {
    return this->jobID;
}

timeType Job::getJobDuration() const {
    return this->jobDuration;
}

timeType Job::getSlackTime() const {
    return this->slackTime;
}

const std::vector<Task> &Job::getTaskList() const {
    return this->taskList;
}

// Dit is ook helemaal beun... Anders werkt de stream operator niet
std::vector<Task> &Job::getTaskList() {
    return this->taskList;
}

bool Job::getTasksAvailable() const{
    for (const Task &task : this->taskList) {
        if (task.getTaskState() == NOT_STARTED) {
            return true;
        }
    }
    return false;
}

bool Job::getJobDone() const{
    for (const Task &task : this->taskList) {
        if (task.getTaskState() != DONE) {
            return false;
        }
    }
    return true;
}

Task &Job::getNextTask() {
    this->sortTasksByID();  // Might not be needed
    auto taskDone = [](const Task &t) {
        return t.getTaskState() == NOT_STARTED;
    };

    auto next = std::find_if(taskList.begin(), taskList.end(), taskDone);
    // if there is a task found that task can be returned
    if (next != taskList.end()) {
        return *next;
    } else {
        // This should never happen, but if it does, return the last task and notify the user.
        std::cerr << "No task found. The output will likely be wrong" <<  '\n';
        return taskList.back();
    }
}

bool Job::isPreviousTaskDone(const Task &t) {
    // If the task is the first task, return true
    if (t.getTaskId() == 0) {
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

    return previousTaskIter->getTaskState() == DONE;
}

//*** Stream operator ***//
std::ostream &operator<<(std::ostream &os, const Job &job) {
    os << "Job ID: " << job.getJobID() <<  '\n';
    os << "Job Duration: " << job.getJobDuration() <<  '\n';
    os << "Slack Time: " << job.getSlackTime() <<  '\n';
    os << "Tasks:" <<  '\n';
    for (const Task &task : job.getTaskList()) {
        os << task <<  '\n';
    }
    return os;
}


void Job::printJobDetails() const {
    std::cout << getJobID() << "\t" << taskList.front().getStartTime() << "\t" << taskList.back().getEndTime() <<  '\n';
}