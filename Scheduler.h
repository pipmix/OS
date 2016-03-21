#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "Process.h"

extern int simulatedCycles;
extern int average;

class Scheduler{

public:


	void ProcessRoundRobin(int interval);
	void ProcessFIFO();
	void ProcessSJF();

	void AddedNewJob();


	vector<Process*> proccesses;


	int rrIterator = 0;

	int m_CycleInterval = 0;
	int m_ContextSwitch = 0;
	bool m_Switching = 0;


	bool m_newJob = 0;

	int m_CurrentJob;
};

#endif