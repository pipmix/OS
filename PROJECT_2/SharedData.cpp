#include "SharedData.h"


// Normal Distribution to get data range with a mean
double ReturnNormalDist(double x, double y) {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	normal_distribution<double> distribution(x, y);
	return distribution(generator);
}

// Generates range 1KB to 100KB with a mean of 20KB
int GetMemoryData() {

	double m_MemoryFootprint;

	do {
		double temp1, temp2;
		temp1 = ReturnNormalDist(20, 80);
		temp2 = ReturnNormalDist(20, 20);
		// Since normal dist works on infinite interval will Truncrate any values the fall outside required values
		if (temp1 < 20) m_MemoryFootprint = temp1;
		else m_MemoryFootprint = temp2;
	} while (m_MemoryFootprint < 1);

	return (int)m_MemoryFootprint;
}

// generates range 1,000 to 11,000 with a mean of 6,000
int GetCycleData() {
	double m_NumberOfCycles;
	do {
		// Since normal dist works on infinite interval will Truncrate any values the fall outside required values
		m_NumberOfCycles = ReturnNormalDist(6000, 5000);;
	} while (m_NumberOfCycles < 1000 || m_NumberOfCycles > 11000);
	return (int)m_NumberOfCycles;
}