#include <iostream>
#include <vector>
#include <thread>
#include "Scheduler.h"


int main(){

	int numberOfProcessors = 4;
	int numberOfProcesses = 10;
	Scheduler scheduler;

	for (int i = 0; i < numberOfProcessors; i++) {
		Processor* temp = new Processor;
		scheduler.AddProcessor(*temp);
	}

	for (int i = 0; i < numberOfProcesses; i++) {
		Process* temp = new Process(i);
		scheduler.AddProcess(*temp);
	}

	while (scheduler.IsProcessing()) {

	}


	return 0;
}