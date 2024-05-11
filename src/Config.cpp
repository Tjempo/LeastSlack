#include "Config.hpp"

config::config(/* args */){
}

config::~config(){
}


void config::readConfigFile(std::string fileName){
	std::ifstream inputFile(fileName);
	if (!inputFile) {
		throw std::runtime_error(
			"Error opening file: " + fileName + "\n" + "Check if it exists");
	}

	std::string line;
	// Skip the first line
	if (!std::getline(inputFile, line)) {
		throw std::runtime_error("Error reading the first line from the file: " + fileName);
	}

	unsigned short jobID = 0;
	// Read and store the remaining lines
	while (std::getline(inputFile, line)){
		// jobs.push_back(job(jobID, line));
		// jobID++;
	}

	// Close the file
	inputFile.close();
}


//*** Getters & Setters ***//

unsigned short config::getAmountOfJobs(){
	return this->amountOfJobs;
}

unsigned short config::getAmountOfMachines(){
	return this->amountOfMachines;
}

