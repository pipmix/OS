#include "ProcessInfo.h"




void ProcessInfo::CreateProcesses(int totalnumofprocesses)
{
	srand(time(NULL));
	for (int i = 0; i < totalnumofprocesses; i++)
	{
		ProcessData PData;
		PData.Pid = g_Data[i].PID;
		PData.Mem = g_Data[i].memory;
		PData.numofCyc = g_Data[i].cycles;
		PData.startTime = g_Data[i].arrival;
		ProcessList.push_back(PData);
		if (g_Debug) cout << "PID:" << std::setw(5) << PData.Pid
					<< "\tcycles:" << std::setw(8) << PData.numofCyc
					<< "\t  memory:" << std::setw(6) << PData.Mem << " kb     "
					<< "start:" << std::setw(6) << PData.startTime << endl;
	}


}

int ProcessInfo::GetMemory()
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);

	std::poisson_distribution<int> distribution(20);
	while (true) {
		int number = distribution(generator);
		if (number >= 1 && number <= 100)
			if (TotalProcessMem += number < 20000)
				TotalProcessMem += number;
	}
	distribution.reset();
}


int ProcessInfo::GetCycles() {
	double m_NumberOfCycles;
	do {
		// Since normal dist works on infinite interval will Truncrate any values the fall outside required values
		m_NumberOfCycles = ReturnNormalDist(6000, 5000);;
	} while (m_NumberOfCycles < 1000 || m_NumberOfCycles > 11000);
	return (int) m_NumberOfCycles;
}

void ProcessInfo::SetandReset()
{
	cyclesElapsed = 0;
	counter = 0;
	ProcessesCompleted = 0;
}

void ProcessInfo::Problem1()
{
	SetandReset();
	ProcessData Info;
	vector <ProcessData> ProcessestoFree;
	while (ProcessesCompleted < ProcessList.size())
	{

		if (cyclesElapsed % 50 == 0 && counter < ProcessList.size())
		{
			cout << "Allocating Memory for Process " << ProcessList[counter].Pid << endl;
			Info = ProcessList[counter];
			Info.MemoryPtr = malloc(Info.Mem);
			Info.Malloced = 1;
			ProcessestoFree.push_back(Info);
			counter++;
			cyclesElapsed++;
		}
		if (ProcessestoFree.size() > 0)
		{

			for (int i = 0; i < ProcessestoFree.size(); i++)
			{
				if (ProcessestoFree[i].Malloced == 1 && ProcessestoFree[i].numofCyc == 0)
				{
					cout << "Freeing Memory for Process " << ProcessestoFree[i].Pid << endl;

					free(ProcessestoFree[i].MemoryPtr);
					ProcessestoFree[i].Malloced = 0;
					ProcessesCompleted++;
				}
				ProcessestoFree[i].numofCyc--;
			}
		}
		cyclesElapsed++;


	}
	SetandReset();
}
