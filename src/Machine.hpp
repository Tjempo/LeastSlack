#ifndef MACHINE_HPP_
#define MACHINE_HPP_

typedef unsigned long long int timeType;

class Machine
{
private:
    timeType availabeAtTime = 0;
    
public:
    Machine(/* args */);
    ~Machine();
    timeType getAvailabeAtTime();
    bool getBusy(timeType currentTime);
    void startMachine(unsigned short currentTime, unsigned short duration);
};

#endif /* MACHINE_HPP_ */
