#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

class config
{
private:
    unsigned short amountOfJobs;
	unsigned short amountOfMachines;
public:
    config(/* args */);
    ~config();
    void readConfigFile(std::string fileName);

    unsigned short getAmountOfJobs();
    unsigned short getAmountOfMachines();
};

