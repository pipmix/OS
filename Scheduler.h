#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "Process.h"
//extern counters
extern int simulatedCycles;
extern int waitAverage;
extern int cycleAverage;
extern int noCompletedProcess;
extern int noOfContextSwitches;

class Scheduler{

public:

	// Single Core
	void ProcessRoundRobin(int interval);
	void ProcessFIFO();
	void ProcessSJF();

	// Multi Core
	void ProcessRoundRobin_MC(int interval);
	void ProcessFIFO_MC();
	void ProcessSJF_MC();

	// Functions
	void AddedNewJob();
	Process* GetShortestProcess();

	// Variables
	vector<Process*> proccesses;
	Process* processors[4];

	int rrIterator = 0;
	int m_CycleInterval = -1;
	int m_ContextSwitch = 0;
	bool m_Switching = 0;
	bool m_newJob = 0;
	int m_CurrentJob;
	bool init = true;
	int m_FifoIt = 0;

	// Multicore Context Switch 
	bool MultiCoreCS[4];
	int MultiCoreCSCount[4];
	int m_processorCycleInterval[4];

};

#endif