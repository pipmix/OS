#pragma once
#include "Process.h"






class MemManage{

public:


	MemManage(int s);

	bool AddProcess(Process*);


	bool MyMalloc(Process* p);
	void MyFree(Process* p);

	~MemManage();


	vector<Process*> proccesses;


private:

	int m_Size;
	vector<MemBlock*> m_Blocks;


	char* m_MemoryBlock;


	MemBlock root;
	MemBlock* currentMemory;
};

