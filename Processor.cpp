#include "Processor.h"

Processor::Processor() {

	m_IsProcessing = false;

}

Processor::~Processor() {
}
	
bool Processor::QueryProcessing() {

		return m_IsProcessing;
}

void Processor::RunProcess(Process& p){

		m_IsProcessing = true;

		cout << "PID: " << p.m_PID << "is starting processing, will process for " << p.m_Cycles << endl;

		async(launch::async, [&]{
			this_thread::sleep_for(chrono::milliseconds(p.m_Cycles * 10));
			cout << p.m_PID << " has finished processing " << endl;
			m_IsProcessing = false;
		});

}