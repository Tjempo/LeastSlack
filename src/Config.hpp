#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


class config
{
private:
    unsigned short amountOfJobs;
	unsigned short amountOfMachines;

    std::vector<std::vector<unsigned short>> configData; //Vector that stores vectors of unsigned shorts 
public:
    config(/* args */);
    ~config();

    void readConfig(const std::string & fileName);
    void readFirstLine(const std::string & fileName);
    void readTasks(const std::string & fileName);

    unsigned short getAmountOfJobs() const;
    unsigned short getAmountOfMachines() const;
    const std::vector<std::vector<unsigned short>>& getConfigVector() const;
    void printConfigData();
};

std::ostream& operator<<(std::ostream &os, const config &conf);

