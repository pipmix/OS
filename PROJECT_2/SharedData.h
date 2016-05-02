#ifndef SHAREDDATA_H
#define SHAREDDATA_H

#include <random>
#include <chrono>
using namespace std;

extern int g_pid;
extern int g_arrive;
extern int g_MemCount;


double ReturnNormalDist(double x, double y);
int GetMemoryData();
int GetCycleData();

struct GlobalData {		// Global Data Set to ensure group members accessed the same set of data

	int PID;
	int memory;
	int cycles;
	int arrival;
	GlobalData() {
		PID = 1000 + (++g_pid);
		memory = GetMemoryData();
		cycles = GetCycleData();
		arrival = g_arrive;
		g_arrive += 50;
		g_MemCount += memory;
	}
	void Print() {
		cout << "PID:" << std::setw(5) << PID
			<< "\tCYCLES:" << std::setw(8) << cycles
			<< "\t  MEM:" << std::setw(6) << memory << " kb     "
			<< "ARRIVAL:" << std::setw(6) << arrival << endl;
	}

};

struct MemBlock {

	int start, size;
	bool Malloced;
	void* MemoryPtr;

	MemBlock* prev;
	MemBlock* next;

	MemBlock() {
		next = nullptr;
		prev = nullptr;
	}


};




#endif