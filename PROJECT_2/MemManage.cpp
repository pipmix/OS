#include "MemManage.h"



MemManage::MemManage(int s){

	m_Size = s;
	m_MemoryBlock = (char*)malloc(m_Size);

	//m_Blocks.push_back(new MemBlock(0, m_Size));


	root.start = 0;
	root.size = 0;
	
	


}


MemManage::~MemManage(){

	free(m_MemoryBlock);
}


bool MemManage::AddProcess(Process* p) {



	proccesses.push_back(p);
	MyMalloc(p);


	return 1;
}


bool MemManage::MyMalloc(Process* p) {

	
	if (root.next == nullptr) {

		root.next = &p->memory;
		p->memory.prev = &root;
		currentMemory = &p->memory;

	}
	else {

		p->memory.prev = currentMemory;
		currentMemory = &p->memory;
		


	}


	p->memory.start = (p->memory.prev->start + p->memory.prev->size) + 1;
	p->memory.size = p->m_MemoryFootprint;

	cout << "  ALLOCATED " << std::setw(5) << p->m_MemoryFootprint << " kb at  " << std::setw(6) << p->memory.start << " kb / 20000 kb" << endl;

	return 1;


}


bool MemManage::MyFree(Process* p) {

	p->InUse = 0;


	cout << "\tDe-allocated " << std::setw(5) << p->m_MemoryFootprint << " kb at " << std::setw(6) << p->memory.start << " kb / 20000 kb at cycle " << g_SimulatedCycles << endl;

	return 1;


}

int MemManage::Update() {

	int FinishedProcesses = 0;

	for (auto* i : proccesses) 
		if  (i->Update() )FinishedProcesses += MyFree(i);					// Free the memory when process completes
	
	return FinishedProcesses;

}