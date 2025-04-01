#include <filesystem>
#include <iostream>

#include "Config.hpp"
#include "JobShop.hpp"

// Main function:
int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Error: Missing file path argument." <<  '\n';
        return 1;
    } else if (argc > 2) {
        std::cerr << "Error: Too many arguments." <<  '\n';
        return 1;
    }

    if (std::filesystem::path(argv[1]).extension() != ".txt") {
        std::cerr << "Error: File path must be a .txt file." <<  '\n';
        return 1;
    }

    // Try to run the program:
    try {
        // Read file & Create Jobs:
        Config conf(argv[1]);

        // Run the program:
        JobShop JS(conf);
        JS.run();

        return 0;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << "Program failed with exception: " <<  '\n' << e.what() <<  '\n';
        return 1;
    }
}
