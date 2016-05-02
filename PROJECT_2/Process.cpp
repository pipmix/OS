#include "Process.h"

Process::Process(int i) {


	// Gets data from global data to ensure all processes use same test data
	m_ProcessID = g_Data[i].PID;
	m_StartTime = g_Data[i].arrival;
	m_NumberOfCycles = g_Data[i].cycles;
	m_MemoryFootprint = g_Data[i].memory;


	cout << "Init: ";
	this->Print();

}


void Process::Print() {
	// This function is for IO and prints the tuples inside the class
	cout << "PID:" << std::setw(5) << m_ProcessID
		<< "\tCYCLES:" << std::setw(8) << m_NumberOfCycles
		<< "\tMEM:" << std::setw(6) << m_MemoryFootprint << " kb     "
		<< "START:" << std::setw(6) << m_StartTime ;
}


bool Process::Update() {
	
	if ((m_StartTime + m_NumberOfCycles) == g_SimulatedCycles)return 1;

	return 0;
}