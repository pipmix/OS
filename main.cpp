#include "Scheduler.h"

extern int simulatedCycles = 0;
extern int processID = 10001;




int main() {

	Scheduler scheduler;

	int noProcesses = 50;
	int noCompletedProcess = 0;
	int processCount = 0;

	while (simulatedCycles < 100000) {

		if (processCount < noProcesses)
			if (simulatedCycles % 50 == 0) {
				scheduler.proccesses.push_back(new Process);
				scheduler.AddedNewJob();
				processCount++;
			}

		//scheduler.ProcessRoundRobin(50);
		//scheduler.ProcessFIFO();
		scheduler.ProcessSJF();
		simulatedCycles++;

	}






	return 0;
}