#ifndef PROCESS_H
#define PROCESS_H

// includes
#include <iostream>
#include <iomanip>  
#include <random>
#include <chrono>
#include <deque>
#include <vector>
using namespace std;
// extern counters
extern int simulatedCycles;
extern int processID;
extern int waitAverage;
extern int cycleAverage;
extern int noCompletedProcess;

class Process {

public:

	Process();
	// Functions
	bool BeginProcessing();
	void DeltaWait();
	void CompleteProcess();
	double ReturnNormalDist(double x, double y);

	// Variables
	int m_PID;
	int m_Cycles;

	// Counters 
	int m_WaitTime;
	int m_InitalCycles;
	int m_StartTime;
	int m_TimesProcessedOn = 0;
	bool m_NewProcess = true;
	bool m_Taken = false;
	bool m_Complete = false;
};
#endif