#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "Processor.h"



class Scheduler {
	public:
					Scheduler				();
					~Scheduler				();

		void		AddProcessor			(Processor& proc);
		void		AddProcess				(Process& proc);

		bool		IsProcessing			();

		void		GetAvailableProcessor	();
		Process*	GetNextProcess			();

	private:

		vector<Processor*>	m_ProcessorList;
		vector<Process*>	m_ProcessList;
		int m_NumberOfProcessors = 0;

		int loc = 0;
		bool sorted = 0;

};

#endif