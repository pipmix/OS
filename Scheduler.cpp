#include "Scheduler.h"


void Scheduler::AddedNewJob() {
	m_newJob = true;
}


void Scheduler::ProcessRoundRobin(int interval) {

	if (proccesses.size() == 0)return;

	if (m_Switching) {
		if (m_ContextSwitch < 10)m_ContextSwitch++;
		else
			m_Switching = false;

	}
	else {
		if (m_CycleInterval < 50) {

			if (m_CycleInterval == 0)proccesses[rrIterator]->DeltaWait();

			if (proccesses[rrIterator]->BeginProcessing()) {
				// Process Completes
				proccesses[rrIterator]->CompleteProcess();
				proccesses.erase(proccesses.begin() + rrIterator);
				rrIterator--;
				m_CycleInterval = 50;
			}
			else m_CycleInterval++;


		}
		if (m_CycleInterval == 50) {
			rrIterator++;
			if (rrIterator == proccesses.size())rrIterator = 0;
			m_CycleInterval = 0;
			m_Switching = true;

		}

	}
}


void Scheduler::ProcessFIFO() {
	
	if (proccesses.size() == 0)return;

	if (m_Switching) {
		if (m_ContextSwitch < 10)m_ContextSwitch++;
		else
			m_Switching = false;

	}
	else {

		if (m_CycleInterval == 0) {
			m_Switching = true;
			proccesses[0]->DeltaWait();
			m_CycleInterval++;
		}
		else {

			if (proccesses[0]->BeginProcessing()) {
				proccesses[0]->CompleteProcess();
				proccesses.erase(proccesses.begin());
				m_CycleInterval = 0;

			}
		}
	}



}

void Scheduler::ProcessSJF() {

	if (proccesses.size() == 0)return;

	if (m_Switching) {
		if (m_ContextSwitch < 10)m_ContextSwitch++;
		else
			m_Switching = false;

	}
	else {

		if (m_newJob == false) {


			if (m_CycleInterval == 0) {
				m_Switching = true;
				proccesses[m_CurrentJob]->DeltaWait();
				m_CycleInterval++;
			}
			else {

				if (proccesses[m_CurrentJob]->BeginProcessing()) {
					proccesses[m_CurrentJob]->CompleteProcess();
					proccesses.erase(proccesses.begin()+ m_CurrentJob);
					m_CurrentJob = 0;
					m_CycleInterval = 0;

				}
			}





		}
		else {

			m_CurrentJob = 0;

			for (int i = 0; i < proccesses.size(); i++) 
				if (proccesses[i]->m_Cycles < proccesses[m_CurrentJob]->m_Cycles) {
					m_CurrentJob = i;
					m_CycleInterval = 0;
				}

			m_newJob = false;
		}




	}



}