#include "Process.h"


Process::Process(int pid){

	m_PID = pid + 00000;
	m_Cycles = rand() % 1000;
	m_Memory = rand() % 100;

}

Process::~Process() {

}