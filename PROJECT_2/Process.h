#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <iomanip>  
#include <random>
#include <chrono>
#include <malloc.h>
#include <vector>


extern int g_MemoryFootprint;
extern int g_SimulatedCycles;
extern int g_MemCount;
extern int g_ProcessID;
extern int g_StartTime;


using namespace std;


struct MemBlock {

	int start, size;
	MemBlock* prev;
	MemBlock* next;

	MemBlock() {
		next = nullptr;
		prev = nullptr;
	}


};


class Process {

public:

	Process();
	~Process();
	double      ReturnNormalDist(double x, double y);
	void        Print();
	void		InsertId(int x);



	int     m_ProcessID;
	int     m_NumberOfCycles;
	int     m_MemoryFootprint;

	int		m_StartTime;

	int m_arrivalTime;

	bool Update();


	Process* prev;
	Process* next;
	int memStart;
	bool InUse;

	MemBlock memory;


	bool Running;
};

#endif // PROCESS_H
