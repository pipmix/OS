#include "Scheduler.h"

extern int simulatedCycles = 0;
extern int processID = 01;
extern int waitAverage = 0;
extern int cycleAverage = 0;
extern int noCompletedProcess = 0;


int main() {

	Scheduler scheduler;

	int noProcesses = 50;
	int processCount = 0;
	int choice = 0;
	cout << "1: Round Robin\n2: FIFO\n3: SJF\n4. Round Robin (Multi Core)\n5. FIFO (Multi Core)\n6. SJF (Multi Core)\nEnter 1-6: ";
	cin >> choice;

	while (noCompletedProcess < noProcesses ) {

		if (processCount < noProcesses)
			if (simulatedCycles % 50 == 0) {
				scheduler.proccesses.push_back(new Process);
				scheduler.AddedNewJob();
				processCount++;
			}

		switch(choice){
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
				scheduler.ProcessRoundRobin(50);
				break;
			case 5:
				scheduler.ProcessFIFO_MC();
				break;
			case 6:
				scheduler.ProcessSJF_MC();
				break;

		}
		simulatedCycles++;
	}

	cout << "PID" << "\t" << "cycles" << "\t" << "wTime" << "\t" << "Times Processed On" << endl;
	cout << "WAIT AVERAGE: " << waitAverage/50 << "\t" << "Cycle Average: " << cycleAverage/50  << endl;

	return 0;
}