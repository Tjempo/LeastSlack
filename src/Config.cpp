#include "Config.hpp"

//*** Constructors & Destructor ***//

Config::Config(const std::string &fileName) : amountOfJobs(0), amountOfMachines(0) {
    this->readConfig(fileName);
}

Config::~Config() = default;

//*** Methods ***//

void Config::readConfig(const std::string &fileName) {
    std::ifstream inputFile(fileName);
    if (!inputFile) {
        throw std::runtime_error("Error opening file: " + fileName + "\nCheck if it exists");
    }

    this->readFirstLine(inputFile);
    this->readTasks(inputFile);
}

void Config::readFirstLine(std::ifstream &input) {
    // Read first line and extract values:
    input >> this->amountOfJobs >> this->amountOfMachines;
}



void Config::readTasks(std::ifstream &input) {
    std::string line;
    this->ConfigData.reserve(amountOfJobs);

    // Skip the first line
    if (!std::getline(input, line)) {
        throw std::runtime_error("Error reading the first line of the file");
    }

    while (std::getline(input, line)) {
        if (line.empty()) { // Skip empty lines
            continue;
        }

        // Create a stringstream to parse the current job line
        std::istringstream jobStream(line);
        unsigned short value;
        std::vector<unsigned short> currentJob;

        // Read and store values from the current job line
        while (jobStream >> value) {
            currentJob.emplace_back(value);
        }

        // Store the current job data in the class:
        this->ConfigData.emplace_back(currentJob);

        // Break if the number of jobs read exceeds or equals the specified count
        if (this->ConfigData.size() >= this->amountOfJobs) {
            break;
        }
    }
}


//*** Steam operator ***//
std::ostream &operator<<(std::ostream &os, const Config &conf) {
    os << "Amount of jobs: " << conf.getAmountOfJobs() <<  '\n';
    os << "Amount of machines: " << conf.getAmountOfMachines() <<  '\n';
    return os;
}