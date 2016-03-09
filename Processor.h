#ifndef PROCESSOR_H
#define PROCESSOR_H
#include "Process.h"

class Processor {

	public:
					Processor			();
					~Processor			();

		bool		QueryProcessing		();
		void		RunProcess			(Process& p);

	private:
		int			m_CurrentPID;
		Process*	m_CurrentProcess;
		bool		m_IsProcessing;
};
#endif