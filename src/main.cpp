#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

//Function defs:
std::string selectFile();
void readFile(std::string);

int main(int argc, char **argv) {
	readFile(selectFile());
	return 0;
}

std::string selectFile() {
	//Define and initialize local variables:
	std::string config = "<unknown>";
	char ans = 'n';

	std::cout << "Enter configuration filename:" << std::endl;
	std::cin >> config;

	//Check with user:
	std::cout << "Selected: " << "./config/" << config << ".txt" << " Proceed? (y/n)" << std::endl;
	std::cin >> ans;

	if (ans == 'n') {
		return selectFile();
	} else {
		std::cout << "./config/"+config <<std::endl;
		return config;
	}
}


void readFile(const std::string fileName) {
	// Open file with exception handling:
	std::cout << "FileName: "<< fileName << std::endl;

	std::ifstream inputFile("./config/" + fileName + ".txt");
	if (!inputFile) {
		throw std::runtime_error("Error opening file: " + fileName + + "\n" + "Check if it exists");
	}

	// Read first line and extract values:
	unsigned short value1, value2;
	inputFile >> value1 >> value2;
	if (!inputFile) {
		throw std::runtime_error("Error reading values from first line");
	}

	// Display values:
	std::cout << "Jobs: " << value1 << std::endl;
	std::cout << "Machines: " << value2 << std::endl;

	// Lees de rest van de file:
	//ToDo: Alles opsplitsen in verschillende jobs / task + duration

	std::string line;
	while (std::getline(inputFile, line)) {
		std::cout << line << std::endl;
	}
}

