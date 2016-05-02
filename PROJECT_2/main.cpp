#include "MemManage.h"

// Externs //
int g_SimulatedCycles = 0;
int g_MemCount = 0;
int g_ProcessID = 1000;
int g_pid = 0;
int g_arrive = 0;
int g_NoOfProc = 64;
GlobalData* g_Data;

// Prototypes //
void RunMemManager(int mem);


// Main //
int main() {
	cout << "--------------------------------------------------" << endl;
	cout << "How many Processes? :    ";
	cin >> g_NoOfProc;


	g_Data = new GlobalData [g_NoOfProc];
	cout << "--------------------------------------------------" << endl;
	cout << "Created a set of " << g_NoOfProc << " Processes totaling  " << g_MemCount << " kb" << endl;
	cout << "--------------------------------------------------" << endl;

	while (1) {

		int processMemory = 0;
		int selection = 0;
		cout << "Which Problem would you like to run: \n"
			<< "1. Problem 1: 20 mb, malloc, free\n"
			<< "2. Problem 2: 20 mb, custom allocators\n"
			<< "3. Problem 3a: 50% of the memory (" << g_MemCount / 2 << " kb) \n"
			<< "4. Problem 3b: 10% of the memory (" << g_MemCount / 10 << " kb) \n"
			<< "5. Custom Memory Amount\n"
			<< "6. View the global processes set\n"
			<< "7. Exit program\n"
			<< "Please enter 1-7: ";

		cin >> selection;



		if (selection == 1) {

			ProcessInfo process;
			process.CreateProcesses(64);
			auto start = chrono::high_resolution_clock::now();

			process.Problem1();

			auto finish = chrono::high_resolution_clock::now();
			cout << chrono::duration_cast<chrono::milliseconds>(finish - start).count() << "ms\n";

		}
		else if (selection == 2) RunMemManager(20000);
		else if (selection == 3) RunMemManager(g_MemCount / 2);
		else if (selection == 4) RunMemManager(g_MemCount / 10);
		else if (selection == 5) {
			cout << "Enter amount of memory in kb : ";
			cin >> processMemory;
			RunMemManager(processMemory);
		}
		else if (selection == 6) for (auto i = 0; i < g_NoOfProc; i++)g_Data[i].Print();
		else if (selection == 7) break;

	}

	return 0;
}

void RunMemManager(int mem) {

	MemManage memoryManager(mem);
	int noCompletedProcess = 0, processCount = 0;
	auto start = chrono::high_resolution_clock::now();
	while (noCompletedProcess < g_NoOfProc) {

		if (processCount < g_NoOfProc)
			if (g_SimulatedCycles % 50 == 0)
				processCount += memoryManager.AddProcess(new Process(processCount));
		noCompletedProcess += memoryManager.Update();
		g_SimulatedCycles++;
	}
	auto finish = chrono::high_resolution_clock::now();
	cout << chrono::duration_cast<chrono::milliseconds>(finish - start).count() << "ms\n";
}