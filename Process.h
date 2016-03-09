#ifndef PROCESS_H
#define PROCESS_H

#include <future>
#include <iostream>
using namespace std;


class Process {

	public:

		Process(int pid);
		~Process();

		int m_PID;
		int m_Cycles;
		int m_Memory;
};

#endif