#ifndef MEMMANAGE_H
#define MEMMANAGE_H



#include "ProcessInfo.h"






class MemManage{

public:


	MemManage(int s);

	bool AddProcess(Process*);


	bool MyMalloc(Process* p);
	bool MyFree(Process* p);
	int Update();

	void GetDataSet(vector<ProcessInfo> p);

	~MemManage();


	vector<Process*> proccesses;
	vector<ProcessInfo> processInfo;

private:

	int m_Size;
	vector<MemBlock*> m_Blocks;




	char* m_MemoryBlock;


	MemBlock root;
	MemBlock* currentMemory;
};

#endif