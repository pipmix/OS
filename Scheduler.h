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
		double		GetDelta				();

		void		StartAndProcess			();

	private:

		vector<Processor*>	m_ProcessorList;
		vector<Process*>	m_ProcessList;

		int loc = 0;
		bool sorted = 0;

		time_point<system_clock> start, end;

		double timeVar;


};

#endif
