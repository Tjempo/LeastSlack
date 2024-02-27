#include "global.h"
#include "JobShop.h"

int main(int argc, char **argv) {
	//Try path to file:
	try {
		std::string path = argv[1];
		//Make new JobShop using args:
		JobShop Job = JobShop(path);
		return 0;
	} catch (const std::exception &e) {
		std::cerr << "Error: " << "Program expects at least one argument," << std::endl << e.what() << std::endl;
		return 1; // Indicate error to the system (optional)
	}
}

