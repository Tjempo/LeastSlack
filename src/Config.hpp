#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Config {
   private:
    unsigned short amountOfJobs;
    unsigned short amountOfMachines;

    std::vector<std::vector<unsigned short>> ConfigData;  // Vector that stores vectors of unsigned shorts
   public:
    Config(/* args */);
    ~Config();

    void readConfig(const std::string& fileName);
    void readFirstLine(const std::string& fileName);
    void readTasks(const std::string& fileName);

    unsigned short getAmountOfJobs() const;
    unsigned short getAmountOfMachines() const;
    const std::vector<std::vector<unsigned short>>& getConfigVector() const;
    void printConfigData();
};

std::ostream& operator<<(std::ostream& os, const Config& conf);

#endif  // CONFIG_HPP