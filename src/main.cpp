#include "JobShop.h"
#include <iostream>

int main(int argc, char **argv) {
	if (argc < 2) {
    	std::cerr << "Error: Missing file path argument." << std::endl;
    	return 1;
	}
	//Try to run the program:
	try {
		std::string path = argv[1]; //Make JobShop using argv[1]:
		JobShop js = JobShop(path);
		js.schedule();
		return 0;
	} catch (const std::exception &e) {
		std::cerr << "Error: " << "Program failed with exception: " << std::endl << e.what() << std::endl;
		return 1;
	}
}

