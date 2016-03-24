#include "Scheduler.h"

// Operating Systems Project 1: Group 14:
// Matthew Escobedo // Nsoh Atanga // Eberechi Akoma

// Global Variables 
int simulatedCycles = 0;
int processID = 1;
int waitAverage = 0;
int cycleAverage = 0;
int noCompletedProcess = 0;
int noOfContextSwitches = 0;

int main() {

	Scheduler scheduler;

	// Variables
	int noProcesses = 50;
	int processCount = 0;
	int choice = 0;
	// Input
	cout << "1: Round Robin\n2: FIFO\n3: SJF\n4. Round Robin (Multi Core)\n5. FIFO (Multi Core)\n6. SJF (Multi Core)\nEnter 1-6: ";
	cin >> choice;

	// per loop is 1 cycle, runs until all processess are complete
	while (noCompletedProcess < noProcesses) {  
		// Create 50 processes ever 50 cycles
		if (processCount < noProcesses)
			if (simulatedCycles % 50 == 0) {
				scheduler.proccesses.push_back(new Process);
				scheduler.AddedNewJob();
				processCount++;
			}

		// Runs selected function based on input
		switch (choice) {
		case 1:
			scheduler.ProcessRoundRobin(50);
			break;
		case 2:
			scheduler.ProcessFIFO();
			break;
		case 3:
			scheduler.ProcessSJF();
			break;
		case 4:
			scheduler.ProcessRoundRobin_MC(50);
			break;
		case 5:
			scheduler.ProcessFIFO_MC();
			break;
		case 6:
			scheduler.ProcessSJF_MC();
			break;

		}
		// Increment Cycle
		simulatedCycles++; 
	}
	// Results Output 
		cout << "PID" << "\t" << "cycles" << "\t" << "wTime" << "\t" << "Times Processed On" << endl;
		cout << "WAIT AVERAGE: " << waitAverage / 50 << "\t" << "Cycle Average: " << cycleAverage / 50 << "     # of context switches " << noOfContextSwitches << endl;
		return 0;
}