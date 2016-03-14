#include "Scheduler.h"

Scheduler::Scheduler() {

	start = std::chrono::system_clock::now();

}
Scheduler::~Scheduler() {}

void Scheduler::AddProcessor(Processor& p) {

		m_ProcessorList.push_back(&p);
		m_NumberOfProcessors++;
		cout << "Added processor: " << m_NumberOfProcessors << endl;

}

void Scheduler::AddProcess(Process& p) {
		
		m_ProcessList.push_back(&p);
		cout << "Added " << p.m_PID << " cycles : " << p.m_Cycles << endl;
}

void Scheduler::GetAvailableProcessor(){

	for (int i = 0; i < m_ProcessorList.size(); i++) {

		if (m_ProcessorList[i]->QueryProcessing()) {

			Process* temp = GetNextProcess();
			m_ProcessorList[i]->RunProcess(*temp);

		}


	}


}

Process* Scheduler::GetNextProcess() {
	//sorted = 1;
	//if (sorted == 0) {

		//sort(m_ProcessList.begin(), m_ProcessList.end(), [](const Process& lhs, const Process& rhs) { return lhs.m_Cycles < rhs.m_Cycles; });
		//sorted = 1 ;
	//}


	return m_ProcessList[++loc];

}

bool Scheduler::IsProcessing() {

	cout << "Processlist size = " << m_ProcessList.size() << endl;

	GetDelta();

	if (m_ProcessList.size() > 0) {
		//cout << "GetAvailable" << endl;
		GetAvailableProcessor();
		return 1;
	}
	else
		cout << "Done Getting Available" << endl;
		return 0;
}

double Scheduler::GetDelta() {

	end = system_clock::now();
	duration<double> elapsed_seconds = end - start;
	return elapsed_seconds.count();

}

void Scheduler::StartAndProcess() {



}