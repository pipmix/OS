#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <iomanip>  

#include <malloc.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include "SharedData.h"



extern int g_SimulatedCycles;
extern GlobalData* g_Data;
extern bool g_Debug;


using namespace std;



class Process {

public:

			Process(int i);
			~Process();

	void	Print();
	void	Allocate(char * block);
	void	Deallocate();
	void	WriteToBlock();

	int     m_ProcessID;
	int     m_NumberOfCycles;
	int     m_MemoryFootprint;
	int		m_StartTime;


	int Update();


	Process* prv;
	Process* nxt;
	int memStart;
	bool InUse;

	bool m_Allocated;
	bool m_Complete;
	bool m_ready;

	MemBlock memory;




	bool Running;
};

#endif // PROCESS_H
