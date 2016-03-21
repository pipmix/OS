#include "Process.h"


Process::Process() {


	m_PID = processID++;
	m_WaitTime = 0;
	m_StartTime = simulatedCycles;


	

	cout << "Created PID:" << m_PID << " at " << m_StartTime << " Cycles" << " with " << m_Cycles << " Cycles " << endl;

	// Use normal distribution with mean of 6000 and standard deviation of 5000
	do {
		// Since normal dist works on infinite interval will Truncrate any values the fall outside required values
		m_Cycles = ReturnNormalDist(6000, 5000);;
	} while (m_Cycles < 1000 || m_Cycles > 11000);

	m_InitalCycles = m_Cycles;
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

double Process::ReturnNormalDist(double x, double y){


	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	normal_distribution<double> distribution(x, y);
	return distribution(generator);

}

