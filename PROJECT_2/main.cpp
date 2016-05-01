#include "MemManage.h"


// Externs
int g_MemoryFootprint = 0;
int g_SimulatedCycles = 0;
int g_MemCount = 0;
int g_ProcessID = 1000;


int main() {

	// Local Vars
	int noCompletedProcess = 0, processCount = 0, noProcesses = 64;

	MemManage memoryManager(20000);


	while (noCompletedProcess < noProcesses) {

		if (processCount < noProcesses)
				if (g_SimulatedCycles % 50 == 0) 
					processCount += memoryManager.AddProcess(new Process);

		g_SimulatedCycles++;

	}


	cout << "Total Memory: " << g_SimulatedCycles << endl;

	return 0;
}