#include "MemManage.h"

MemManage::MemManage(int s){

	m_Size = s;
	m_MemoryBlock = (char*)malloc(m_Size);

	pRoot = nullptr;
	pCurrent = nullptr;
	counter = 0;
}

MemManage::~MemManage(){
	free(m_MemoryBlock);
}


bool MemManage::AddProcess(Process* p) {

	proccesses.push_back(p);
	//MyMalloc(p);


	return 1;
}


bool MemManage::MyMalloc(Process* p) {


	int requestBlock = p->m_MemoryFootprint;

	if (pRoot == nullptr) {
		if (g_Debug)cout << "Allocating root" << endl;
		pRoot = p;
		pCurrent = p;
		p->memory.size = requestBlock;
		p->memory.start = 0;
		p->memory.end = p->memory.start + p->memory.size;
		// Assign block of memory to process
		p->Allocate(m_MemoryBlock);
		p->nxt = nullptr;
		if (g_Debug)cout << "Allocated " << p->m_ProcessID << " block: " << p->memory.start << " to " << p->memory.start + p->memory.size << endl;
		return 1;
	}
	else {

		int endOfCurrentBlock = pCurrent->memory.end + 1;

		int memNeeded = endOfCurrentBlock + requestBlock;

		if (pCurrent->nxt == nullptr) {
			if (memNeeded < m_Size) {
				p->memory.size = requestBlock;
				p->memory.start = endOfCurrentBlock;
				p->memory.end = p->memory.start + p->memory.size;
				// Assign block of memory to process
				p->Allocate(m_MemoryBlock);
				pCurrent->nxt = p;
				pCurrent = p;
				pCurrent->nxt = nullptr;

				if (g_Debug)cout << "\tAllocated " << std::setw(4) << p->memory.size << " kb at block [ " << std::setw(6) << p->memory.start << " - " << std::setw(6) << p->memory.end << " ] at cycle " << g_SimulatedCycles << " for PID: " << p->m_ProcessID << endl;

				return 1;
			}
		}
		else {

			while (1) {
				if (memNeeded < pCurrent->nxt->memory.start) {
					p->memory.size = requestBlock;
					p->memory.start = endOfCurrentBlock;
					p->memory.end = p->memory.start + p->memory.size;
					// Assign block of memory to process
					p->Allocate(m_MemoryBlock);
					p->nxt = pCurrent->nxt;
					pCurrent->nxt = p;
					pCurrent = p;
					if (g_Debug)cout << "\tAllocated " << std::setw(4) << p->memory.size << " kb at block [ " << std::setw(6) << p->memory.start << " - " << std::setw(6) << p->memory.end << " ] at cycle " << g_SimulatedCycles << " for PID: " << p->m_ProcessID << endl;

					return 1;
				}
				else {
					pCurrent = pCurrent->nxt;
					if (pCurrent == nullptr) {
						pCurrent = pRoot;
						break;
					}
				}
			}
		}
	}


	int requestBlock2 = p->m_MemoryFootprint;
	int endOfCurrentBlock2 = pCurrent->memory.end + 1;
	int memNeeded2 = endOfCurrentBlock2 + requestBlock2;
	//cout << "last request at " << memNeeded2 << "kb at " << pCurrent->memory.end + 1 << endl;
	return 0;
}


bool MemManage::MyFree(Process* p) {

	if (p == pRoot){
		if (p->nxt == nullptr) {
			if (g_Debug)cout << "All memory is free" << endl;
			pRoot = nullptr;
			
			p->Deallocate();
			if (g_Debug)cout << "\tDe-allocated " << std::setw(4) << p->memory.size << " kb at block [ " << std::setw(6) << p->memory.start << " - " << std::setw(6) << p->memory.end << " ] at cycle " << g_SimulatedCycles << " for PID: " << p->m_ProcessID << endl;

		}
		else {
			if (g_Debug)cout << "Deleting root (compacting next block to location 0 kb)" << endl;
			pRoot = p->nxt;
			//p->nxt = nullptr;
			// if first memory block deleted, move memory forward
			pRoot->memory.start = 0;
			pRoot->memory.end = pRoot->m_MemoryFootprint;
			// null the pointer to char * memoryBlock
			p->Deallocate();
			if (g_Debug)cout << "\tDe-allocated " << std::setw(4) << p->memory.size << " kb at block [ " << std::setw(6) << p->memory.start << " - " << std::setw(6) << p->memory.end << " ] at cycle " << g_SimulatedCycles << " for PID: " << p->m_ProcessID << endl;

		}
	}
	else {
		Process* tempP = pRoot;
		while (1) {
			//if (tempP == nullptr)tempP = pRoot;
			if (tempP->nxt->m_ProcessID == p->m_ProcessID) {
				tempP->nxt = p->nxt;
				p->nxt = nullptr;
				// null the pointer to char * memoryBlock
				p->Deallocate();
				if (g_Debug)cout << "\tDe-allocated " << std::setw(4) << p->memory.size << " kb at block [ " << std::setw(6) << p->memory.start << " - " << std::setw(6) << p->memory.end << " ] at cycle " << g_SimulatedCycles << " for PID: " << p->m_ProcessID << endl;

				break;
			}
			else {
				tempP = tempP->nxt;
			}
		}
	}

	g_FinishedProcess++;

	return 1;

}

int MemManage::Update() {

	for (int i = 0; i < proccesses.size(); i++) {

		// If past start time, insert into ready queue
		if (proccesses[i]->m_StartTime <= g_SimulatedCycles)proccesses[i]->m_ready = true;
		// If in ready queue but not allocated
		if ((proccesses[i]->m_Allocated == false) && (proccesses[i]->m_ready))MyMalloc(proccesses[i]);
		// If allocated 
		if (proccesses[i]->m_Allocated == true)		
			// If process completed
			if ((proccesses[i]->m_StartTime + proccesses[i]->m_NumberOfCycles) <= g_SimulatedCycles) {
				if (g_Debug)cout << "PID: " << proccesses[i]->m_ProcessID << " finished processing " << proccesses[i]->m_NumberOfCycles << " cycles at " << g_SimulatedCycles << " needs de-allocating" << endl;
				// De-Allocate then delete process
				MyFree(proccesses[i]);
				proccesses.erase(proccesses.begin() + i);
				i--;
			}
	}

	counter++;
	
	// Compact the memory every 5000 cycles otherwise #3a and 3b will often get stuck because of memory segmentation
	if (counter == 5000) {
		if (g_Debug)PrintMemoryMap();
		if (g_Debug)cout << "Current Processes running = " << proccesses.size() << endl;
		counter = 0;
		//CompactMemory();
	}

	return 1;

}

void MemManage::PrintMemoryMap() {

	// This function will print the blocks of memory that is allocated
	Process* temp = pRoot;
	if (pRoot == nullptr)cout << " ROOT IS NULL" << endl;
	cout << "-------------------------------------------------------------" << endl;
	cout << "CURRENT MEMORY MAP at " << g_SimulatedCycles << " cycles " << " total size is " << g_MemCount << endl;
	while (temp != nullptr) {

		cout << "PID: " << temp->m_ProcessID << " : Block [ " << setw(4) << temp->memory.start << " - " << setw(4) << temp->memory.end << " ] " << endl;
		temp = temp->nxt;
	}
	cout << "-------------------------------------------------------------" << endl;

}

void MemManage::CompactMemory() {

	// This function moves all the memory blocks to the edge of the previous one
	Process* tempP = pRoot;

	if (g_Debug)if (tempP == nullptr)cout << "All memory free, cannot compact" << endl;
				else cout << "-------------------------------COMPACTING MEMORY--------------------------------------------------------" << endl;

	while (tempP != nullptr) {
		if (tempP->nxt == nullptr)break;
		tempP->nxt->memory.start = tempP->memory.end + 1;
		tempP->nxt->memory.end = tempP->nxt->memory.start + tempP->nxt->memory.size;
		tempP = tempP->nxt;
	}
}