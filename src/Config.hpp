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

    
    [[nodiscard]] inline unsigned short getAmountOfJobs() const noexcept { return amountOfJobs; }
    [[nodiscard]] inline unsigned short getAmountOfMachines() const noexcept { return amountOfMachines; }
    [[nodiscard]] inline const std::vector<std::vector<unsigned short>>& getConfigVector() const noexcept { return ConfigData; }
    void printConfigData();

   private:
    unsigned short amountOfJobs;
    unsigned short amountOfMachines;

    // Functions

    /// @brief Reads the config file and stores the values in the amountOfJobs and amountOfMachines variables
    /// @param fileName filename of the .txt file
    void readConfig(const std::string& fileName);

    /// @brief Extracts the first line of the file and stores the values in the amountOfJobs and amountOfMachines variables
    /// @param input ifstream object
    void readFirstLine(std::ifstream& input);

    /// @brief Reads the tasks from the file and stores them in the ConfigData vector
    /// @param input ifstream object
    void readTasks(std::ifstream& input);

    std::vector<std::vector<unsigned short>> ConfigData;  // Vector that stores vectors of unsigned shorts
};

std::ostream& operator<<(std::ostream& os, const Config& conf);

#endif  // CONFIG_HPP