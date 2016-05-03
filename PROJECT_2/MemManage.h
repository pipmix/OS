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

	char* m_MemoryBlock;

	//MemBlock* root;
	//MemBlock* tail;
	//MemBlock* current;

	Process* pRoot;
	Process* pCurrent;
};

#endif