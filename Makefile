# Compiler and libraries
CXX = g++
CXXFLAGS = -Wall -Wextra -Wconversion -pedantic -std=c++17 -O3 -flto
SRC_FOLDER = src
OUTPUT_FOLDER = $(SRC_FOLDER)/output
OUTPUT_FILE = $(OUTPUT_FOLDER)/app

# OS detection (if Windows, append .exe to output)
OS := $(shell uname -s)
ifeq ($(OS), Windows_NT)
	OUTPUT_FILE := $(OUTPUT_FOLDER)/app.exe
endif

# Find all source files in the src folder
SRC_FILES = $(wildcard $(SRC_FOLDER)/*.cpp)

# Object files will be placed in the output folder
OBJ_FILES = $(patsubst $(SRC_FOLDER)/%.cpp, $(OUTPUT_FOLDER)/%.o, $(SRC_FILES))

# Target to build object files and link them
build: $(OUTPUT_FOLDER) $(OUTPUT_FILE)

# Compile each .cpp file into .o in the output folder
$(OUTPUT_FOLDER)/%.o: $(SRC_FOLDER)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link the object files into the final executable
$(OUTPUT_FILE): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ_FILES) $(CLIBS)

# Create the output folder if it doesn't exist
$(OUTPUT_FOLDER):
	mkdir -p $(OUTPUT_FOLDER)

# Run the program from the output folder
run: $(OUTPUT_FILE)
	./$(OUTPUT_FILE) ./configs/$(CONFIG)

# Clean up the output folder
clean:
	rm -f $(OUTPUT_FOLDER)/*
ifeq ($(OS), Windows_NT)
	del /Q $(subst /,\,$(OUTPUT_FOLDER))\*
endif

test: build
	python3 ./__test__/evaluate.py

benchmark: build
	python3 ./__test__/benchmark.py


cppcheck:
	cppcheck --enable=all --inconclusive --std=c++17 --force --suppress=missingIncludeSystem $(SRC_FOLDER) 2> cppcheck_report.txt || true
	@echo "cppcheck finished. Review 'cppcheck_report.txt' for details."

# Make sure to build the program with -o0 for valgrind
valgrind: build
	valgrind --leak-check=full --track-origins=yes --track-fds=yes --show-leak-kinds=all ./$(OUTPUT_FILE) ./configs/$(CONFIG)
