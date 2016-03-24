#include "Scheduler.h"

void Scheduler::AddedNewJob() {
	m_newJob = true;												// Flags scheduler that a new job was added, for use in pre emptive SJF
}


void Scheduler::ProcessRoundRobin(int interval) {

	if (proccesses.size() == 0)return;								// Abort if no processes in queue

	if (m_Switching) {												// If context switching
		if (m_ContextSwitch < 10)m_ContextSwitch++;
		else {
			m_Switching = false;									// context switching complete
			m_ContextSwitch = 0;
		}
	}
	else {
		if (m_CycleInterval < 50) {												// Run process for 50 cycles

			if (m_CycleInterval == 0)proccesses[rrIterator]->DeltaWait();		// calculate the delta waiting time

			if (proccesses[rrIterator]->BeginProcessing()) {					// processes process 1 cycle
				proccesses[rrIterator]->CompleteProcess();						// return 1 means process completed
				proccesses.erase(proccesses.begin() + rrIterator);				// remove process from queue
				rrIterator--;													// move iterator back one
				m_CycleInterval = 50;											// reset interval
			}
			else m_CycleInterval++;												// incrment interval
		}
		if (m_CycleInterval == 50) {											// Runs if quantum interval complete
			rrIterator++;														// Moves iterator forward
			if (rrIterator == proccesses.size())rrIterator = 0;
			m_CycleInterval = 0;
			m_Switching = true;													// context switch
			noOfContextSwitches++;
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
			noOfContextSwitches++;
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
		if (m_newJob == false){										// No new jobs added ( this a pre emptive sjf)
			if (m_CycleInterval == -1){								// Switch to new job
				m_Switching = true;
				proccesses[m_CurrentJob]->DeltaWait();
				m_CycleInterval = 0;
				noOfContextSwitches++;
			}
			else {
				if (proccesses[m_CurrentJob]->BeginProcessing()) {				//  process current
					proccesses[m_CurrentJob]->CompleteProcess();
					proccesses.erase(proccesses.begin()+ m_CurrentJob);			// remove since completed
					m_CurrentJob = 0;											// reset 
					m_CycleInterval = -1;
				}
			}
		}
		else {														// If a new job
			m_CurrentJob = 0;
			for (int i = 0; i < proccesses.size(); i++)										
				if (proccesses[i]->m_Cycles < proccesses[m_CurrentJob]->m_Cycles) {			// keep a iterator at shortest job and compares each job in queue to it
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
						noOfContextSwitches++;
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

Process* Scheduler::GetShortestProcess() {															// This returns shortest job in the queue

	if (proccesses.size() == 0) return nullptr;															// Abort if emtpy
	
	int temp = -1;																			// -1 is used in case proccess 0 is taken and there are no other process in queue
	
	for (int i = 0; i < proccesses.size(); i++) {											//Cylcle through processes
		
		if (proccesses[i]->m_Taken == true || proccesses[i]->m_Complete == true)continue;    // this makes sure shortest process isnt taken or complete
		else{
			temp = i;
			break;
		}
	}
	
	if (temp == -1)return nullptr;																				// if proccess 0 is taken and there are no other process in queue
	for (int i = 0; i < proccesses.size(); i++) {
		if (proccesses[i]->m_Cycles < proccesses[temp]->m_Cycles) {
			if (proccesses[i]->m_Taken == true || proccesses[i]->m_Complete == true) continue;
			else temp = i;
		}
	}
	if (proccesses[temp]->m_Taken == true || proccesses[temp]->m_Complete == true)return nullptr;	// if taken or complete return null 
	else
		return proccesses[temp];																	 // This will return the shorst job

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
					//cout << "ALLOCATE ALLOCATE: " << processors[i]->m_PID << endl;
					m_Switching = true;	
					noOfContextSwitches++;
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
				else;													// keep on processing
			}	
		}
	}
}

void Scheduler::ProcessRoundRobin_MC(int interval) {


// First run init --------------------------------------

	if (proccesses.size() == 0)return;									// Abort if queue empty

	if (init)															// First run processor initiliazation
		for (int i = 0; i < 4; i++) {
			processors[i] = nullptr;
			MultiCoreCS[i] = false;										// MultiCore Context Switch
			MultiCoreCSCount[i] = 0;
			init = false;
		}	// end processor init


// Load up processors --------------------------------------
		for (int i = 0; i < 4; i++) {													// Cycle through Processors
			
			if (processors[i] == nullptr && proccesses.size() != 0) {					// Load Process to Available Processor
				processors[i] = proccesses[0];							
				proccesses.erase(proccesses.begin());									// Removes from front of queue, when done with quantom will place in back
			}
		} 


 // Run the  processors --------------------------------------
		for (int i = 0; i < 4; i++) {

			if (MultiCoreCS[i] == true) {										// Processor Context Switch
				if (MultiCoreCSCount[i] < 10) MultiCoreCSCount[i]++;			// Context switch for 10 cycles
				else {
					MultiCoreCSCount[i] = 0;									// End Context Switch
					MultiCoreCS[i] = false;
				}
			}
			else {																// Processor is not context switching
				if (processors[i] != nullptr) {									// If processor not empty
					if (m_processorCycleInterval[i] < 50) {						// Run process for 50 cycles

						if (m_processorCycleInterval[i] == 0)processors[i]->DeltaWait();			// calculate the delta waiting time

						if (processors[i]->BeginProcessing()) {					// Processes 
							processors[i]->CompleteProcess();					// Process completes
							delete processors[i];
							processors[i] = nullptr;
							m_processorCycleInterval[i] = 50;
						}
						else {
							m_processorCycleInterval[i]++;						// Process needs to continue
						}
					}


					if (m_processorCycleInterval[i] == 50) {										// quantum fullfilled on this processor
						m_processorCycleInterval[i] = 0;											// Reset quantum
						MultiCoreCS[i] = true;
						noOfContextSwitches++;
						rrIterator++;
						if (rrIterator == proccesses.size())rrIterator = 0;							// Reset  iterator if at end
						proccesses.push_back(processors[i]);
					}
				}
			}
		}
	
}