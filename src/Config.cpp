#include "Config.hpp"

//*** Constructors & Destructor ***//

Config::Config(/* args */){
}

Config::~Config(){
}


//*** Methods ***//

void Config::readConfig(const std::string &fileName) {
	this->readFirstLine(fileName);
	this->readTasks(fileName);
}


void Config::readFirstLine(const std::string &fileName) {
	std::ifstream inputFile(fileName);
	if (!inputFile) {
		throw std::runtime_error("Error opening file: " + fileName + +"\n" + "Check if it exists");
	}

	// Read first line and extract values:
	inputFile >> this->amountOfJobs >> this->amountOfMachines;

	std::cout << "Amount of jobs: " << this->amountOfJobs << std::endl;
	std::cout << "Amount of machines: " << this->amountOfMachines << std::endl;

	// Close file:
	inputFile.close();
}



void Config::readTasks(const std::string &fileName) {
    std::ifstream inputFile(fileName);
    std::string line;

    // Check if file exists
    if (!inputFile) {
        throw std::runtime_error("Error opening file: " + fileName + "\n" + "Check if it exists");
    }

    // Skip the first line
    if (!std::getline(inputFile, line)) {
        throw std::runtime_error("Error reading the first line from the file: " + fileName);
    }

    while (std::getline(inputFile, line)) {
        // Skip empty lines
        if (line.empty()) {
            continue;
        }

        // Create a stringstream to parse the current job line
        std::istringstream jobStream(line);
        unsigned short value;
        std::vector<unsigned short> currentJob;

        // Read and store values from the current job line
        while (jobStream >> value) {
            currentJob.push_back(value);
        }

        // Store the current job data in the class:
        ConfigData.push_back(currentJob);

        // Break if the number of jobs read exceeds or equals the specified count
        if (ConfigData.size() >= this->amountOfJobs) {
			printConfigData(); 
            break;
        }
    }
}



//*** Getters & Setters ***//

unsigned short Config::getAmountOfJobs() const{
	return this->amountOfJobs;
}

unsigned short Config::getAmountOfMachines() const{
	return this->amountOfMachines;
}

const std::vector<std::vector<unsigned short>>& Config::getConfigVector() const {
	return this->ConfigData;
}


//*** Steam operator ***//
std::ostream& operator<<(std::ostream &os, const Config &conf) {
	os << "Amount of jobs: " << conf.getAmountOfJobs() << std::endl;
	os << "Amount of machines: " << conf.getAmountOfMachines() << std::endl;
	return os;
}

//For debugging purposes:
void Config::printConfigData(){
	// Print the entire vector after the loop
    std::cout << "Jobs Vector:" << std::endl;
    for (const auto &job : ConfigData) {
        for (unsigned short value : job) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
}