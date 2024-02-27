#include "JobShop.h"

JobShop::JobShop() {
	//Empty :O
}

JobShop::JobShop(std::string filePath) {


}

JobShop::~JobShop() {
	// TODO Auto-generated destructor stub
}

JobShop::JobShop(const JobShop &other) {
	// TODO Auto-generated constructor stub

}

void JobShop::readFile(const std::string fileName) {
	// Open file with exception handling:
	std::cout << "FileName: " << fileName << std::endl;

	std::ifstream inputFile(fileName);
	if (!inputFile) {
		throw std::runtime_error( "Error opening file: " + fileName + +"\n" + "Check if it exists");
	}

	if (!inputFile) {
		throw std::runtime_error("Error reading values from first line");
	}

	// Read first line and extract values:
	unsigned short tasks, machines;
	inputFile >> tasks >> machines;

	//Store Values:
	this->nAmountOfMachines = machines;
	this->nAmountOfTasks = tasks;


	// Display values:
	std::cout << "tasks: " << this->nAmountOfTasks << std::endl;
	std::cout << "Machines: " << this->nAmountOfMachines << std::endl;

	// Lees de rest van de file:
	//ToDo: Alles opsplitsen in verschillende tasks / task + duration

	std::string line;
	while (std::getline(inputFile, line)) {
		std::cout << line << std::endl;
	}
}
