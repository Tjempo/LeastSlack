#include "JobShop.h"
#include <algorithm>

/*
 JobShop::JobShop() :
 nAmountOfTasks(0), nAmountOfMachines(0), time(0) {
 for (int i = 0; i < 0; ++i) {
 this->machineState.push_back(false);
 }
 //Empty :O
 }
 */
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
	for (int i = 0; i < machines; ++i) {
		this->machineInUse.push_back(false);
	}

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
		throw std::runtime_error(
				"Error opening file: " + fileName + "\n"
						+ "Check if it exists");
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
		// jobs.push_back(line);
		jobs.push_back(job(jobID, line));
		jobID++;
	}

	// Close the file
	inputFile.close();
}

void JobShop::schedule() {
	calculateSlack(currentTime); //Vraag: Moet hier this-> voor en zoja wat is het nut daarvan? Answer: it is not required to use "this->", it is just to make the code more clear

	/*ToDo:
	 - Bereken Slack < Klaar hoop ik
	 - Bereken total duration < Klaar
	 - Bereken EST (Earliest Start Time)

	 - Sorteer task op basis van slack
	 - Start taak met laagste slack
	 -
	 - Zet taak naar {in progress}
	 */

	taskActivationManager();


	/*//temporarily deactivated for obvious reasons :)
	 while (!allJobsDone()) {
	 	 calculateSlack(currentTime);

	 	 checkTaskProgress();

	 	 sortTasks();

	 	++currentTime;
	 }
	 */

	// printJobResult(); // use \t for the tabs :)
	std::cout << "all Jobs Completed" << std::endl;

}

void JobShop::calculateSlack(unsigned long long &time) {
	for (job &job : jobs) {
		job.calculateEST(time);
		job.calculateTotalDuration();
	}
}

bool JobShop::allJobsDone() {
	for (job &job : jobs) {
		if (!job.isJobDone()) {
			return false; // when a job is not completed, return false right away
		}
	}
	return true;
}

void JobShop::orderJobsByTotalDuration() {
	std::sort(jobs.begin(), jobs.end(), [](const job &job1, const job &job2) {
		return job1 > job2;
	});
}

void JobShop::checkTaskProgress() {
	// placeholder
}

void JobShop::taskActivationManager() { // i have no idea if this is going to function the way i want it to :)
	std::cout
			<< "----------------------------------------------------------------------------------------"
			<< std::endl;
	// debuf print statement
	for (job &job : jobs) {
		std::cout << job << std::endl;
	}

	orderJobsByTotalDuration(); // least slack but different

	std::cout
			<< "---sorted list ----------------------------------------------------------------------------------------"
			<< std::endl;

	std::vector<task> sortedList;

	for (job &job : jobs) {
		std::cout << job << std::endl;
		if (job.getNextTask().getCurrentState() == NOT_COMPLETED
				&& machineInUse[job.getNextTask().getMachineNumber()]
						== false) {
			job.getNextTask().activateTask(currentTime);
			machineInUse[job.getNextTask().getMachineNumber()] = true;
			sortedList.push_back(job.getNextTask());
		}
	}

	for (task task : sortedList) {
		std::cout << task << std::endl;
	}
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

