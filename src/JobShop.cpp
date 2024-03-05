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
JobShop::JobShop(const std::string &filePath) :
		currentTime(0) {
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
		this->machineInUseUntil.push_back(0);
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
	//calculateSlack(currentTime); //Vraag: Moet hier this-> voor en zoja wat is het nut daarvan? Answer: it is not required to use "this->", it is just to make the code more clear

	/*ToDo:
	 - Bereken Slack < Klaar hoop ik
	 - Bereken total duration < Klaar
	 - Bereken EST (Earliest Start Time)

	 - Sorteer task op basis van slack
	 - Start taak met laagste slack
	 -
	 - Zet taak naar {in progress}
	 */

	//taskActivationManager();
	//temporarily deactivated for obvious reasons :)
	while (!allJobsDone()) {
		calculateSlack(currentTime);

		checkJobProgress();

		taskActivationManager();

		if (currentTime >= 140) {
			break;
		}

		++currentTime;
		std::cout << "Current time is: " << currentTime << std::endl;
	}

	// printJobResult(); // use \t for the tabs :)
	std::cout << "all Jobs Completed" << std::endl;

	for (job job : jobs) {
		std::cout << job.getNextTask() << std::endl;
	}

	for (unsigned long long i = 0; i < machineInUseUntil.size(); ++i) {
		std::cout << "Machine in use until: " << machineInUseUntil[i]
				<< std::endl;
	}

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

void JobShop::checkJobProgress() {
	// placeholder
	for (job &job : jobs) { // was hier het fucking & teken vergeten, hij paste dus eerst een lokaal ding aan
		job.checkTaskProgress(currentTime);
	}
}

//void JobShop::deactivateMachine(unsigned short index) {
//	machineInUseUntil[index] = true;
//}

void JobShop::taskActivationManager() { // i have no idea if this is going to function the way i want it to :)

	orderJobsByTotalDuration(); // least slack but different

	std::vector<task> sortedList;

	for (unsigned long long i = 0; i < machineInUseUntil.size(); ++i) {
		std::cout << "Machine in use until: " << machineInUseUntil[i]
				<< std::endl;
	}

	for (job &job : jobs) {
//		std::cout << job << std::endl;
		if (job.getNextTask().getCurrentState() == NOT_COMPLETED
				&& machineInUseUntil[job.getNextTask().getMachineNumber()]
						<= currentTime) {
			std::cout << "activate a task from job with number: "
					<< job.getJobID() << std::endl;
			std::cout << "with machinenumber: "
					<< job.getNextTask().getMachineNumber() << std::endl;
			machineInUseUntil[job.getNextTask().getMachineNumber()] =
					currentTime + job.getNextTask().getDuration();
			job.getNextTask().activateTask(currentTime);
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

