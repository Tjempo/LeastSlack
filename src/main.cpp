#include "global.h"
#include "JobShop.h"

int main(int argc, char **argv) {
	//Try path to file:
	try {
		std::string path = argv[1];
		//Make new JobShop using argv[1]:
		JobShop js = JobShop(path);
		js.schedule();
		return 0;
	} catch (const std::exception &e) {
		std::cerr << "Error: " << "Program failed with exception: " << std::endl << e.what() << std::endl;
		return 1;
		//ToDo: check for args to fix "construction from null is not valid"
	}
}

