#include <iostream>
#include "Scheduler.h"


int main(){

	int processors = 4;
	int processes = 10;
	int counter = 0;

	Scheduler scheduler;

	for (auto i = 0; i < processors; i++) 
			scheduler.AddProcessor(*new Processor);
	

	scheduler.StartAndProcess();

	if (scheduler.GetDelta() > 50 && count < processes ) {


	}

	


	for (int i = 0; i < numberOfProcesses; i++) {
		Process* temp = new Process(i);
		scheduler.AddProcess(*temp);
	}


	return 0;
}