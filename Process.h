#ifndef PROCESS_H
#define PROCESS_H

#include			<iostream>
#include			<chrono>
#include			<future>
using namespace		std;
using namespace		chrono;

class Process {

	public:

		Process		(int pid);
		~Process	();

		int m_PID;
		int m_Cycles;
		int m_Memory;

};

#endif