#include "Process.h"


Process::Process() {


	m_PID = processID++;
	m_Cycles = rand() % 200;
	m_WaitTime = 0;
	m_StartTime = simulatedCycles;


	m_InitalCycles = m_Cycles;

	cout << "Created PID:" << m_PID << " at " << m_StartTime << " Cycles" << " with " << m_Cycles << " Cycles " << endl;

}



void Process::DeltaWait() {

	m_TimesProcessedOn++;
	m_WaitTime += simulatedCycles - m_StartTime;


	
}


bool Process::BeginProcessing() {

	m_Cycles-- ;
	m_StartTime = simulatedCycles++;

	//if (m_Cycles == 0 )

	if (m_Cycles == 0)return 1;
	else
		return 0;


}

void Process::CompleteProcess() {
	cout << "----------------------------------------" << endl;
	cout << "Completed PID: " << m_PID << " at " << simulatedCycles << " cylces" << " with a wait time of " << m_WaitTime << endl;
	cout << "Had " << m_InitalCycles << " cycles, and was processed on " << m_TimesProcessedOn << " times" << endl;
	cout << "----------------------------------------" << endl;

}

