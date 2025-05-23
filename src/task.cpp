#include "Task.hpp"

// *** Constructor and Destructor ***

Task::Task() : taskId(0), machineNumber(0), duration(0), EST(0), startTime(0), endTime(0), state(NOT_STARTED) {
}

Task::Task(unsigned short id, unsigned short machineNr, timeType dur)
    : taskId(id), machineNumber(machineNr), duration(dur), EST(0), startTime(0), endTime(0), state(NOT_STARTED) {
}

// Copy constructor
Task::Task(const Task &RHS)
    : taskId(RHS.taskId), machineNumber(RHS.machineNumber), duration(RHS.duration), EST(RHS.EST), startTime(RHS.startTime), endTime(RHS.endTime), state(RHS.state) {
}

// Destructor
Task::~Task() {
}

// *** Logic Operators ***

// Less Than Operator:
bool Task::operator<(const Task &RHS) const {
    return this->taskId < RHS.taskId;
}

// Assignment Operator:
Task &Task::operator=(const Task &RHS) {
    if (this != &RHS) {
        taskId = RHS.taskId;
        machineNumber = RHS.machineNumber;
        duration = RHS.duration;
        EST = RHS.EST;
        startTime = RHS.startTime;
        endTime = RHS.endTime;
        state = RHS.state;
    }
    return *this;
}

// Equality Operator:
bool Task::operator==(const Task &RHS) const {
    return this->taskId == RHS.taskId;  // Consider more attributes if needed
}

// *** Getters and Setters ***

unsigned short Task::getTaskId() const {
    return this->taskId;
}

timeType Task::getTaskDuration() const {
    return this->duration;
}

unsigned short Task::getMachineNumber() const {
    return this->machineNumber;
}

timeType Task::getEST() const {
    return this->EST;
}

timeType Task::getStartTime() const {
    return this->startTime;
}

timeType Task::getEndTime() const {
    return this->endTime;
}

taskState Task::getTaskState() const {
    return this->state;
}

// *** Setters ***

void Task::setEST(timeType newEST) {
    this->EST = newEST;
}

void Task::setTaskDone() {
    this->state = DONE;
}

// *** Functions ***

void Task::startTask(timeType startTime) {
    this->startTime = startTime;
    this->endTime = startTime + this->duration;
    this->state = STARTED;
}

// *** Stream Operator ***

std::ostream &operator<<(std::ostream &os, const Task &t) {
    os << "Task Number: " << t.getTaskId();
    os << " On Machine: " << t.getMachineNumber();
    os << " Duration: " << t.getTaskDuration();
    os << " EST: " << t.getEST();
    os << " Start Time: " << t.getStartTime();
    os << " End Time: " << t.getEndTime() <<  '\n';
    os << " Task State: " << t.getTaskState() <<  '\n';
    return os;
}
