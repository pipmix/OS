#ifndef PROCESSINFO_H
#define PROCESSINFO_H
#include "Process.h"


extern int g_SimulatedCycles;
extern bool g_Debug;


extern GlobalData* g_Data;

struct ProcessData
{
	int Pid;
	int numofCyc;
	int Mem;
	int startTime;
	bool Malloced;
	void* MemoryPtr;

};

class ProcessInfo
{
public:

	int GetMemory();
	int GetCycles();
	void CreateProcesses(int);
	void SetandReset();
	void Problem1();
	//~ProcessInfo();

private:

	vector <ProcessData> ProcessList;
	int cyclesElapsed;
	int counter;
	int ProcessesCompleted;
	int TotalProcessMem;
};


#endif