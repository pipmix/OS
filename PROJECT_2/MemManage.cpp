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

	cout << "\tALLOCATED " << p->m_MemoryFootprint << " kb at  " << p->memory.start << " / 20000 kb" << endl;

	return 1;


}


void MemManage::MyFree(Process* p) {


	cout << "\tDe-allocated " << p->m_MemoryFootprint << " kb at memory location " << p->memory.start << "of 20,000 kb." << endl;



}


