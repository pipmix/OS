#ifndef MEMMANAGE_H
#define MEMMANAGE_H

#include "ProcessInfo.h"

extern int g_FinishedProcess;


class MemManage{

public:


			MemManage			(int s);
			~MemManage			();
	bool	AddProcess			(Process*);
	bool	MyMalloc			(Process* p);
	bool	MyFree				(Process* p);
	int		Update				();

	void	PrintMemoryMap		();

	void	CompactMemory		();


	vector<Process*> proccesses;


private:

	int counter;
	int m_Size;

	// For #2, #3a, 3b - this whole block gets malloc'd once then subdiveded into blocks to be assigned to processes
	char* m_MemoryBlock;


	Process* pRoot;
	Process* pCurrent;
};

#endif