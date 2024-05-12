#include <iostream>
#include <filesystem>

#include "config.hpp"



//Main function:
int main(int argc, char **argv) {
	if (argc < 2) {
    	std::cerr << "Error: Missing file path argument." << std::endl;
    	return 1;
	}else if(argc > 2){
        std::cerr << "Error: Too many arguments." << std::endl;
    	return 1;
    }

    if(std::filesystem::path(argv[1]).extension() != ".txt"){
        std::cerr << "Error: File path must be a .txt file." << std::endl;
        return 1;
    }

	//Try to run the program:
	try {
        //Read file & Create Jobs:
		config conf;
		conf.readConfig(argv[1]);
		//Run the program:

		// JobShop jobShop(conf);

		// jobShop.run();
		
		return 0;
	}
    catch (const std::exception &e) {
		std::cerr << "Error: " << "Program failed with exception: " << std::endl << e.what() << std::endl;
		return 1;
	}
}


