#include "Process.h"

Process::Process(int i) {

	// Gets data from global data containter (g_Data) to ensure all processes use same test data
	m_ProcessID = g_Data[i].PID;
	m_StartTime = g_Data[i].arrival;
	m_NumberOfCycles = g_Data[i].cycles;
	m_MemoryFootprint = g_Data[i].memory;
	m_Allocated = false;
	m_Complete = false;
	m_ready = false;

	memory.size = m_MemoryFootprint;


	if (g_Debug)cout << "Init: ";
	if (g_Debug)this->Print();

}

void Process::Print() {
	// This function is for IO and prints the tuples inside the class
	cout << "PID:" << std::setw(5) << m_ProcessID
		<< "\tCYCLES:" << std::setw(8) << m_NumberOfCycles
		<< "\tMEM:" << std::setw(6) << m_MemoryFootprint << " kb     "
		<< "START:" << std::setw(6) << m_StartTime << endl;
}


int Process::Update() {

	/*
	if (m_StartTime == g_SimulatedCycles)m_ready = true;						// Goes into ready queue to have its memory allocated 

	if (m_ready) {																// If in ready queue
		if (m_Allocated) {														// If ready and allocated
			if ((m_StartTime + m_NumberOfCycles) <= g_SimulatedCycles) {		// If Process complete
				cout  << "PID: " << m_ProcessID << " finished processing " << m_NumberOfCycles << " cycles at " << g_SimulatedCycles << " needs de-allocating"<< endl;
				return 1;
			}
			else {																// If ready and allocated but not finished processing
				return 0;
			}// Since we are not scheduling the process will simply complete at start time + number of cycles + any off set from waiting for memory
		}
		else {
			// says the process is in the ready queue but still needs to be allocated memory
			return 2; 
		}
	}
	*/
	return 0;
}

void Process::Allocate(char * m) { 
	// Point memoryblock to the pre-Malloc'd block
	memory.MemoryPtr = m;
	// update the start time once process actually has allocated memory
	m_StartTime = g_SimulatedCycles;
	m_Allocated = true;
}

void Process::Deallocate(){
	// Set memory pointer to null before deleting process
	memory.MemoryPtr = nullptr;
	m_Complete = true;
}

void Process::WriteToBlock() {

	// This code was to allocate actual memory to the memory blocks however dillion said this was unnesccary

	//memccpy( *(memory.MemoryPtr + memory.start)  , memory.MemoryPtr, sizeof(char) * memory.size  );



}