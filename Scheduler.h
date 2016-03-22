#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "Process.h"

extern int simulatedCycles;
extern int waitAverage;
extern int cycleAverage;
extern int noCompletedProcess;


class Scheduler{

public:


	void ProcessRoundRobin(int interval);
	void ProcessFIFO();
	void ProcessSJF();


	void ProcessRoundRobin_MC(int interval);
	void ProcessFIFO_MC();
	void ProcessSJF_MC();

	int GetShortestJob();

	Process* GetShortestProcess();

	void AddedNewJob();


	vector<Process*> proccesses;


	int rrIterator = 0;

	int m_CycleInterval = -1;
	int m_ContextSwitch = 0;
	bool m_Switching = 0;


	bool m_newJob = 0;

	int m_CurrentJob;

	//vector<Process*> processors;

	Process* processors[4];


	bool init = true;
	int m_FifoIt = 0;

	bool p1newProcess = true;
	bool p2newProcess = true;
	bool p3newProcess = true;
	bool p4newProcess = true;

	int m_P1_CycleIt = -1;
	int m_P2_CycleIt = -1;
	int m_P3_CycleIt = -1;
	int m_P4_CycleIt = -1;


};

#endif