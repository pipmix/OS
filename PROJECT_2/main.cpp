#include "MemManage.h"


	

// Externs
int g_MemoryFootprint = 0;
int g_SimulatedCycles = 0;
int g_MemCount = 0;
int g_ProcessID = 1000;
int g_StartTime = 0;



int main() {

	auto start = std::chrono::high_resolution_clock::now();


	// Local Vars
	int noCompletedProcess = 0, processCount = 0, noProcesses = 64;

	vector<Process*> processes(64);

	MemManage memoryManager(20000);


	while (noCompletedProcess < noProcesses) {

		if (processCount < noProcesses)
				if (g_SimulatedCycles % 50 == 0) 
					processCount += memoryManager.AddProcess(new Process);



		noCompletedProcess += memoryManager.Update();

		g_SimulatedCycles++;

	}


	cout << "Total Memory: " << g_SimulatedCycles << endl;

	auto finish = std::chrono::high_resolution_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() << "ns\n";

	return 0;
}