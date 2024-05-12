#include "Config.hpp"


//*** Constructors & Destructor ***//


config::config(/* args */){
}

config::~config(){
}


//*** Methods ***//

void config::readConfig(const std::string &fileName) {
	this->readFirstLine(fileName);
	this->readTasks(fileName);
}


void config::readFirstLine(const std::string &fileName) {
	// Open file with exception handling:
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



void config::readTasks(const std::string &fileName) {
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
        configData.push_back(currentJob);

        // Break if the number of jobs read exceeds or equals the specified count
        if (configData.size() >= this->amountOfJobs) {
			printConfigData(); 
            break;
        }
    }
}



//*** Getters & Setters ***//

unsigned short config::getAmountOfJobs() const{
	return this->amountOfJobs;
}

unsigned short config::getAmountOfMachines() const{
	return this->amountOfMachines;
}

const std::vector<std::vector<unsigned short>>& config::getConfigVector() const {
	return this->configData;
}



//*** Steam operator ***//
std::ostream& operator<<(std::ostream &os, const config &conf) {
	os << "Amount of jobs: " << conf.getAmountOfJobs() << std::endl;
	os << "Amount of machines: " << conf.getAmountOfMachines() << std::endl;
	return os;
}

//For debugging purposes:
void config::printConfigData(){
	// Print the entire vector after the loop
    std::cout << "Jobs Vector:" << std::endl;
    for (const auto &job : configData) {
        for (unsigned short value : job) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
}