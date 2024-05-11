#ifndef MACHINE_HPP_
#define MACHINE_HPP_

typedef unsigned long long timeUnit;

class Machine
{
private:
    timeUnit availabeAtTime = 0;
    
public:
    Machine(/* args */);
    ~Machine();
    timeUnit getAvailabeAtTime();
    bool getBusy(timeUnit currentTime);
    void startMachine(unsigned short currentTime, unsigned short duration);
};

#endif /* MACHINE_HPP_ */
