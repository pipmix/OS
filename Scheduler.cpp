#include "Scheduler.h"


void Scheduler::AddedNewJob() {
	m_newJob = true;												// Flags scheduler that a new job was added, for use in SJF
}


void Scheduler::ProcessRoundRobin(int interval) {

	if (proccesses.size() == 0)return;								// Abort if no processes in queue

	if (m_Switching) {												// If context switching
		if (m_ContextSwitch < 10)m_ContextSwitch++;
		else {
			m_Switching = false;
			m_ContextSwitch = 0;
		}
	}
	else {
		if (m_CycleInterval < 50) {												// Run process for 50 cycles

			if (m_CycleInterval == 0)proccesses[rrIterator]->DeltaWait();		// calculate the delta waiting time

			if (proccesses[rrIterator]->BeginProcessing()) {
				proccesses[rrIterator]->CompleteProcess();
				proccesses.erase(proccesses.begin() + rrIterator);
				rrIterator--;
				m_CycleInterval = 50;
			}
			else m_CycleInterval++;
		}
		if (m_CycleInterval == 50) {
			rrIterator++;
			if (rrIterator == proccesses.size())rrIterator = 0;
			m_CycleInterval = 0;
			m_Switching = true;

		}

	}
}


void Scheduler::ProcessFIFO() {
	
	if (proccesses.size() == 0)return;								// Abort if no processes in queue

	if (m_Switching){												// Context Switch wait 10 cycles
		if (m_ContextSwitch < 10)m_ContextSwitch++;
		else {
			m_ContextSwitch = 0;									// End Context Switch
			m_Switching = false;
		}
	}
	else {															// else if not context switching
		if (m_CycleInterval == -1) {								// start processing new process
			m_Switching = true;										// new process so start context switch
			proccesses[0]->DeltaWait();								// new process, add in the waiting time 
			m_CycleInterval = 0;
		}
		else {														// continue processing current process
			if (proccesses[0]->BeginProcessing() == 1) {			// run process for a cycle, return 0 if process does not finish
				proccesses[0]->CompleteProcess();					// wrap up process debug code
				proccesses.erase(proccesses.begin());				// remove process from queue
				m_CycleInterval = -1;								// reset cycle count
			}
			else {
				m_CycleInterval++;									// keep on processing
			}
		}
	}
}

void Scheduler::ProcessSJF() {

	if (proccesses.size() == 0)return;								// Abort if queue empty
	if (m_Switching) {												// If context switching
		if (m_ContextSwitch < 10) m_ContextSwitch++;				// Wait for 10
		else {														// Reset Context Switch
			m_Switching = false;
			m_ContextSwitch = 0;
		}
	}
	else {															// If not context switching
		if (m_newJob == false){										// No new jobs added
			if (m_CycleInterval == -1){								// Switch to new job
				m_Switching = true;
				proccesses[m_CurrentJob]->DeltaWait();
				m_CycleInterval = 0;
			}
			else {
				if (proccesses[m_CurrentJob]->BeginProcessing()) {
					proccesses[m_CurrentJob]->CompleteProcess();
					proccesses.erase(proccesses.begin()+ m_CurrentJob);
					m_CurrentJob = 0;
					m_CycleInterval = -1;
				}
			}
		}
		else {														// If a new job
			m_CurrentJob = 0;
			for (int i = 0; i < proccesses.size(); i++) 
				if (proccesses[i]->m_Cycles < proccesses[m_CurrentJob]->m_Cycles) {
					m_CurrentJob = i;
					m_CycleInterval = 0;
				}
			m_newJob = false;
		}
	}
}


void Scheduler::ProcessFIFO_MC() {

	if (proccesses.size() == 0)return;								// Abort if queue empty

	if (init)														// First run processor initiliazation
		for (int i = 0; i < 4;i++) {
			processors[i] = nullptr;
			init = false;
		}															// end processor init
	
	if (m_Switching){
		if (m_ContextSwitch < 10)m_ContextSwitch++;
		else{
			m_ContextSwitch = 0;									// End Context Switch
			m_Switching = false;
		}
	}

	// Load up Processors with processes

	else {
		for (int i = 0; i < 4; i++) {								// cycle through processors
			if (processors[i] == nullptr) {							// If process is available
				if (m_FifoIt >= proccesses.size());					// No processes in queue, leave processor available
				else {												// Processor is available
					processors[i] = proccesses[m_FifoIt];			// grab process
					//cout << "PROCESSOR " << i + 1 << " now has PID: " << processors[i]->m_PID << endl;
					m_FifoIt++;										// forward iterator 
				}
			}
		}

	// Run processes that have processes

			for (int i = 0; i < 4; i++) {							// Processor Run
				if (processors[i] != nullptr) {
					if (processors[i]->m_NewProcess) {				// If new process run a context switch
						m_Switching = true;
						processors[i]->DeltaWait();
						processors[i]->m_NewProcess = false;
					}
					else {											// If not a new process then no context switch
						if (processors[i]->BeginProcessing()) {		// Run process
							processors[i]->CompleteProcess();		// wrap up process debug code
							processors[i] = nullptr;
						} 
						else {
							;										// Keep on processing process on this processor
						}
					}
				} // End Processor Run
			}	
	}
}

Process* Scheduler::GetShortestProcess() {

	if (proccesses.size() == 0) return nullptr;


	int temp = 0;

	for (int i = 0; i < proccesses.size(); i++) {
		if (proccesses[i]->m_Cycles < proccesses[temp]->m_Cycles) {
			if (proccesses[i]->m_Taken == true || proccesses[i]->m_Complete == true) continue;
			else temp = i;
		}
	}

	if (proccesses[temp]->m_Taken == true || proccesses[temp]->m_Complete == true)return nullptr;
	else
		return proccesses[temp];

}

int Scheduler::GetShortestJob() {

	if (proccesses.size() == 0) return -1;

	int temp = 0;
	for (int i = 0; i < proccesses.size(); i++){						// cycle through processes
		if (proccesses[i]->m_Cycles < proccesses[temp]->m_Cycles) {		// keep track of lowest cycle time
			if (proccesses[i]->m_Complete==false)
				if (proccesses[temp]->m_Taken == false)temp = i;
			
		}
	}

	if (proccesses[temp]->m_Taken == true)return -1;
	if (proccesses[temp]->m_Complete == true)return -1;

	proccesses[temp]->m_Taken = true;
	return temp;
	
		

}


void Scheduler::ProcessSJF_MC() {

	if (proccesses.size() == 0)return;									// Abort if queue empty

	if (init)															// First run processor initiliazation
		for (int i = 0; i < 4; i++) {
			processors[i] = nullptr;
			init = false;
		}	// end processor init

	if (m_Switching) {													// Context Switch
		if (m_ContextSwitch < 10)m_ContextSwitch++;						// Context switch for 10 cycles
		else {
			m_ContextSwitch = 0;										// End Context Switch
			m_Switching = false;
		}
	}
	else {

		// Allocate Available process
		for (int i = 0; i < 4; i++){
			if (processors[i] == nullptr){	// processor avaiable
				processors[i] = GetShortestProcess();					// Return shortest job
				if (processors[i] != nullptr) {
					processors[i]->m_Taken = true;
					processors[i]->DeltaWait();							//  calculate the delta wait time
					cout << "ALLOCATE ALLOCATE: " << processors[i]->m_PID << endl;
					//m_Switching = true;				
				}
			}
		}
		// Run processors
		for (int i = 0; i < 4; i++) {									// Run processes on Loaded cores
			if (processors[i] != nullptr) {
				if (processors[i]->BeginProcessing()) {
					processors[i]->CompleteProcess();						// completed processes
					processors[i]->m_Complete = true;
					processors[i] = nullptr;								// Set Processor as available
				}
				else {
					;														// keep on processing
				}
			}	
		}
	}
}

void Scheduler::ProcessRoundRobin_MC(int interval) {

	if (proccesses.size() == 0)return;									// Abort if queue empty

	if (init)															// First run processor initiliazation
		for (int i = 0; i < 4; i++) {
			processors[i] = nullptr;
			init = false;
		}	// end processor init

	if (m_Switching) {													// Context Switch
		if (m_ContextSwitch < 10)m_ContextSwitch++;						// Context switch for 10 cycles
		else {
			m_ContextSwitch = 0;										// End Context Switch
			m_Switching = false;
		}
	}
	else {
		// Load up processors
		for (int i = 0; i < 4; i++) {
			rrIterator = 0;
			if (processors[i] == nullptr) {
				if (rrIterator >= proccesses.size())processors[i] == nullptr;
				if (proccesses[rrIterator]->m_Taken == 1)processors[i] == nullptr;
				else {
					processors[i] == proccesses[i];
					processors[i]->m_Taken = true;
					m_Switching = true;
				}
			}
		}
		// Run the processesors
		for (int i = 0; i < 4; i++) {

				int tempCycle;
				if (i == 0)tempCycle = m_P1_CycleIt;
				else if (i == 1)tempCycle = m_P2_CycleIt;
				else if (i == 2)tempCycle = m_P3_CycleIt;
				else if (i == 3)tempCycle = m_P4_CycleIt;

				if (tempCycle < 50) {												// Run process for 50 cycles

					if (tempCycle == 0)processors[i]->DeltaWait();		// calculate the delta waiting time

					if (processors[i]->BeginProcessing()) {
						processors[i]->CompleteProcess();
						processors[i] = nullptr;
						tempCycle = 50;
					}
					else tempCycle++;
				}
				if (tempCycle == 50) {
					processors[i]->m_Taken = false;
					tempCycle = 0;
					m_Switching = true;
				}
				if (i == 0)m_P1_CycleIt = tempCycle;
				else if (i == 1)m_P2_CycleIt = tempCycle;
				else if (i == 2)m_P3_CycleIt = tempCycle;
				else if (i == 3)m_P4_CycleIt = tempCycle;
		}
	}
}