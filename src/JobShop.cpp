#include "JobShop.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

/*
 JobShop::JobShop() :
 nAmountOfTasks(0), nAmountOfMachines(0), time(0) {
 for (int i = 0; i < 0; ++i) {
 this->machineState.push_back(false);
 }
 //Empty :O
 }
 */
JobShop::JobShop(const std::string &filePath) :
		currentTime(0) {
	this->readFile(filePath);
}

JobShop::~JobShop() {
	// Destructor stub
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
	for (int i = 0; i < machines; ++i) {
		this->machineInUseUntil.push_back(0);
	}

	this->nAmountOfMachines = machines;
	this->nAmountOfTasks = tasks;

	// Close file:
	inputFile.close();
}

void JobShop::readTasks(const std::string &fileName) {
	std::ifstream inputFile(fileName);

	if (!inputFile) {
		throw std::runtime_error(
			"Error opening file: " + fileName + "\n" + "Check if it exists");
	}

	std::string line;

	// Skip the first line
	if (!std::getline(inputFile, line)) {
		throw std::runtime_error(
				"Error reading the first line from the file: " + fileName);
	}

	unsigned short jobID = 0;
	// Read and store the remaining lines
	while (std::getline(inputFile, line)) {
		jobs.push_back(job(jobID, line));
		jobID++;
	}

	// Close the file
	inputFile.close();
}

void JobShop::schedule() {
	/*ToDo:
	 - Bereken Slack < Klaar hoop ik
	 - Bereken total duration < Klaar
	 - Bereken EST (Earliest Start Time) < Klaar

	 - Sorteer task op basis van slack
	 - Start taak met laagste slack
	 - {Als taak gelijke slack heeft op basis van ID sorteren}
	 - Zet taak naar {in progress}
	 */

	while (!allJobsDone()) {
		calculateSlack(currentTime);

		checkJobProgress();

		taskActivationManager();

		++currentTime;
		std::cout << "Current time is: " << currentTime << std::endl;
	}

	printJobResults();
	std::cout << "##### All Jobs Completed #####" << std::endl;

}

void JobShop::calculateSlack(unsigned long long &time) {
	for (job &job : jobs) {
		job.calculateEST(time);
		job.calculateTotalDuration();
	}
}

bool JobShop::allJobsDone() {
	for (job &job : jobs) {
		if (job.isJobDone() == false) {
			return false; // When a job is not completed, return false right away
		}
	}
	return true;
}

void JobShop::orderJobsByTotalDuration() {
	std::sort(jobs.begin(), jobs.end(), [](const job &job1, const job &job2) {
		return job1 > job2;
	});
}

void JobShop::checkJobProgress() {
	for (job &job : jobs) {
		job.checkTaskProgress(currentTime);
	}
}

//void JobShop::deactivateMachine(unsigned short index) {
//	machineInUseUntil[index] = true;
//}

void JobShop::printJobResults() {
	std::cout << "call: printJobResults()" << std::endl;
	for (job &job : jobs) {
		job.printJobDetails();
	}
}

void JobShop::taskActivationManager() {
	orderJobsByTotalDuration();
	std::vector<task> sortedList;

	/*
	for (unsigned long long i = 0; i < machineInUseUntil.size(); ++i) {
		std::cout << "Machine in use until: " << machineInUseUntil[i]
				<< std::endl;
	}
	*/

	for (job &job : jobs) {
		if (job.getNextTask().getCurrentState() == NOT_COMPLETED && machineInUseUntil[job.getNextTask().getMachineNumber()] <= currentTime) {
			// std::cout << "activate a task from job with number: " << job.getJobID() << std::endl;
			// std::cout << "with machinenumber: " << job.getNextTask().getMachineNumber() << std::endl;
			machineInUseUntil[job.getNextTask().getMachineNumber()] =
					currentTime + job.getNextTask().getDuration();
			job.getNextTask().activateTask(currentTime);
			sortedList.push_back(job.getNextTask());
		}
	}
	/*
	for (task task : sortedList) {
		std::cout << task << std::endl;
	}
	*/
}

//Getters:
unsigned short JobShop::getAmountOfTasks() const {
	return this->nAmountOfTasks;
}

unsigned short JobShop::getAmountOfMachines() const {
	return this->nAmountOfMachines;
}

const std::vector<job> JobShop::getJobs() const {
	return this->jobs;
}