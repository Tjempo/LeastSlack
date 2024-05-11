#include "Machine.hpp"


//*** Constructor and Destructor ***

Machine::Machine(){}

Machine::~Machine() {}



//*** Getters & Setters***

timeUnit Machine::getAvailabeAtTime() {
	return availabeAtTime;
}

bool Machine::getBusy(timeUnit currentTime){
    return currentTime < availabeAtTime;
}

void Machine::startMachine(unsigned short currentTime, unsigned short duration) {
	availabeAtTime = currentTime + duration;
}