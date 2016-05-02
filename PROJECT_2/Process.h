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

using namespace std;



class Process {

public:

			Process(int i);
			~Process();

	void	Print();


	int     m_ProcessID;
	int     m_NumberOfCycles;
	int     m_MemoryFootprint;
	int		m_StartTime;
	int		m_arrivalTime;

	bool Update();


	Process* prev;
	Process* next;
	int memStart;
	bool InUse;

	MemBlock memory;


	bool Running;
};

#endif // PROCESS_H
