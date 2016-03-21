#include "Process.h"


Process::Process() {


	m_PID = processID++;
	m_WaitTime = 0;
	m_StartTime = simulatedCycles;

	do {
		m_Cycles = ReturnNormalDist(6000, 5000);;
	} while (m_Cycles < 1000 || m_Cycles > 11000);

	m_InitalCycles = m_Cycles;
	cycleAverage += m_InitalCycles;

	cout << "Created PID:" << m_PID << " at " << m_StartTime << " Cycles" << " with " << m_Cycles << " Cycles " << endl;
}



void Process::DeltaWait() {

	m_TimesProcessedOn++;
	m_WaitTime += simulatedCycles - m_StartTime;


	
}


bool Process::BeginProcessing() {

	m_Cycles-- ;
	m_StartTime = simulatedCycles++;


	if (m_Cycles == 0)return 1;
	else
		return 0;


}

void Process::CompleteProcess() {

	noCompletedProcess++;

	cout << m_PID << "\t" << m_InitalCycles << "\t" << m_WaitTime << "\t" << m_TimesProcessedOn << endl;

	waitAverage += m_WaitTime;
	


}

double Process::ReturnNormalDist(double x, double y){


	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	normal_distribution<double> distribution(x, y);
	return distribution(generator);

}

