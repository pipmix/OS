#include "Process.h"

Process::Process() {
	// NORMAL DISTRUBTION FROM PROGRAM 2
	m_PID = processID++;
	m_WaitTime = 0;
	m_StartTime = simulatedCycles;
	// because normal distubution works on infinite this clamps it
	do {
		m_Cycles = ReturnNormalDist(6000, 5000);;
	} while (m_Cycles < 1000 || m_Cycles > 11000);

	m_InitalCycles = m_Cycles;
	cycleAverage += m_InitalCycles;
	// debug text
	cout << "Created PID:" << m_PID << " at " << m_StartTime << " Cycles" << " with " << m_Cycles << " Cycles.    At:  " << simulatedCycles << endl;
}

void Process::DeltaWait() { 
	//this function calculates the number of cycles between the current time (only called when process is starting to run) and the last cycle it ran or entered queue ( which isnt neccisarly the start like varible implies )
	m_TimesProcessedOn++;
	int delta = simulatedCycles - m_StartTime;
	m_WaitTime += delta;
	//cout << "BEGIN: " << m_PID << "\t" << m_InitalCycles << "\t" << m_WaitTime << "\t" << "   AT:   "  << simulatedCycles << endl;
}

bool Process::BeginProcessing() {
	// This function decremets a cycle from the cycle count which is "processing" the process
	m_Cycles -= 1;
	m_StartTime = simulatedCycles;

	// Returns 0 if the process has 0 cycles therefore completed
	if (m_Cycles == 0)return 1;
	else
		return 0;
}

void Process::CompleteProcess() {

	noCompletedProcess++;
	cout << "END: " << m_PID << "\t" << m_InitalCycles << "\t" << m_WaitTime << "\t" << m_TimesProcessedOn << "   AT:   " << simulatedCycles << endl;
	waitAverage += m_WaitTime;
}

double Process::ReturnNormalDist(double x, double y){
	
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();		// Normal Distribution from program 1
	std::default_random_engine generator(seed);
	normal_distribution<double> distribution(x, y);
	return distribution(generator);
}