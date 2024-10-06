#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Config {
   public:
    Config() = delete;
    explicit Config(const std::string& fileName);
    ~Config();

    unsigned short getAmountOfJobs() const;
    unsigned short getAmountOfMachines() const;
    const std::vector<std::vector<unsigned short>>& getConfigVector() const;
    void printConfigData();

   private:
    unsigned short amountOfJobs;
    unsigned short amountOfMachines;

    // Functions

    /// @brief Reads the config file and stores the values in the amountOfJobs and amountOfMachines variables
    /// @param fileName filename of the .txt file
    void readConfig(const std::string& fileName);

    /// @brief Extracts the first line of the file and stores the values in the amountOfJobs and amountOfMachines variables
    /// @param fileName filename of the .txt file
    void readFirstLine(const std::string& fileName);

    /// @brief Reads the tasks from the file and stores them in the ConfigData vector
    /// @param fileName filename of the .txt file
    void readTasks(const std::string& fileName);

    std::vector<std::vector<unsigned short>> ConfigData;  // Vector that stores vectors of unsigned shorts
};

std::ostream& operator<<(std::ostream& os, const Config& conf);

#endif  // CONFIG_HPP