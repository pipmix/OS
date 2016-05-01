#include "Process.h"

Process::Process() {

	// Constructor generates cycles and mem
	m_ProcessID = g_ProcessID++;
	m_StartTime = g_SimulatedCycles;

	// Use normal distribution with mean of 6000 and standard deviation of 5000
	do {
		// Since normal dist works on infinite interval will Truncrate any values the fall outside required values
		m_NumberOfCycles = ReturnNormalDist(6000, 5000);;
	} while (m_NumberOfCycles < 1000 || m_NumberOfCycles > 11000);

	// Use 2 normal distributions
	// temp1 is mean 20 standard deviaion of 80
	// temp2 is mean 20 standard devation of 20
	// Any value less than 20 will use SD of 20 
	// Any value over 20 will use SD of 80
	do {

		double temp1, temp2;

		temp1 = ReturnNormalDist(20, 80);
		temp2 = ReturnNormalDist(20, 20);
		// Since normal dist works on infinite interval will Truncrate any values the fall outside required values
		if (temp1 < 20) m_MemoryFootprint = temp1;
		else m_MemoryFootprint = temp2;
	} while (m_MemoryFootprint < 1);



	g_MemoryFootprint += m_MemoryFootprint;

	cout << "CREATED:  ";
	this->Print();





}

Process::~Process() {

}

double Process::ReturnNormalDist(double x, double y) {

	// This function takes two values, x = the mean and y is the standard deviaion

	// Seed random with the system time
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);


	//use std::normal_distribution function to get random nu,ner
	normal_distribution<double> distribution(x, y);
	// Return the number
	return distribution(generator);

}

void Process::InsertId(int x) {
	// THis function ensures the PID is a unique value by using the for loop in main
	m_ProcessID += x;
}

void Process::Print() {
	// This function is for IO and prints the tuples inside the class
	cout << "PID:" << std::setw(8) << m_ProcessID
		<< "\tCYCLES:" << std::setw(8) << m_NumberOfCycles
		<< "\tMEM:" << std::setw(6) << m_MemoryFootprint << " kb     "
		<< "START:" << std::setw(8) << m_StartTime ;
}