#include "JobShop.h"

#include <regex>

JobShop::JobShop() :
		nAmountOfTasks(0), nAmountOfMachines(0) {
	//Empty :O
}

JobShop::JobShop(const std::string &filePath) {
	this->readFile(filePath);
}

JobShop::~JobShop() {
	// TODO Auto-generated destructor stub
}

JobShop::JobShop(const JobShop &other) {
	// TODO Auto-generated constructor stub

}

void JobShop::readFile(const std::string &fileName) {
	readFirstLine(fileName);
	readTasks(fileName);
}

void JobShop::readFirstLine(const std::string &fileName) {
	// Open file with exception handling:
	std::cout << "FileName: " << fileName << std::endl;

	std::ifstream inputFile(fileName);
	if (!inputFile) {
		throw std::runtime_error(
				"Error opening file: " + fileName + +"\n"
						+ "Check if it exists");
	}

	// Read first line and extract values:
	unsigned short tasks, machines;
	inputFile >> tasks >> machines;

	//Store Values:
	this->nAmountOfMachines = machines;
	this->nAmountOfTasks = tasks;

	// Display values:
	std::cout << "Tasks: " << this->nAmountOfTasks << std::endl;
	std::cout << "Machines: " << this->nAmountOfMachines << std::endl;

	// Close file:
	inputFile.close();
}

void JobShop::readTasks(const std::string &fileName) {
    std::ifstream inputFile(fileName);

    if (!inputFile) {
        throw std::runtime_error("Error opening file: " + fileName + "\n" + "Check if it exists");
    }

    std::string line;

    //ToDo: #Vraag of je rekening moet houden dat er text in kan staan?

    // Skip the first line
    if (!std::getline(inputFile, line)) {
        throw std::runtime_error("Error reading the first line from the file: " + fileName);
    }
    std::regex containsLetters("[a-zA-Z]");
    // Read and store the remaining lines
    while (std::getline(inputFile, line)) {
    	if(!std::regex_match(line, containsLetters)){
        	jobs.push_back(line);
        	//ToDo: #Turn it into a Job using the Job Class
    	}else{
    		std::cout << "Line failed check: " << line << std::endl;
    	}
    }

    // Close the file
    inputFile.close();

    //Print for debug purpose:
    for (size_t i = 0; i < jobs.size(); ++i) {
        std::cout << "Job[" << i << "] = " << jobs[i] << std::endl;
    }
}


