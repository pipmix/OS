#ifndef PROCESS_H
#define PROCESS_H

extern int simulatedCycles;
extern int processID;

#include <iostream>
#include <deque>
#include <vector>
using namespace std;


class Process {

public:

	Process();

	bool BeginProcessing();
	void DeltaWait();
	void CompleteProcess();



	int m_PID;
	int m_Cycles;

	int m_InitalCycles;



	int m_WaitTime;
	int m_StartTime;


	int m_TimesProcessedOn = 0;

};





#endif