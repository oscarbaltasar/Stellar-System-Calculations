#include "SystemSimulation.h"

SystemSimulation::SystemSimulation(Planet* planets, SystemCenter* systemCenter, User* user)
{
	//realTime = new std::tm();
	this->planets = planets;
	this->systemCenter = systemCenter;
	this->user = user;
}

void SystemSimulation::run()
{
	long DebugTime = 100000;
	while (true) {
		//get reallife time
		auto start = std::chrono::high_resolution_clock::now();
		this->UpdateRealTime();

		//FIRST STEP
		//Calculate planets position according to time
		int numberofPlanets = sizeof(*planets) / sizeof(Planet);
		for (int i = 0; i < numberofPlanets; i++) {
			planets[i].CalculateGlobalPosition(DebugTime);
			std::cout << planets[i].toString();
			planets[i].CalculateSatelitesPositions(DebugTime);
			
		}
	}
}

void SystemSimulation::UpdateRealTime() {
	time(&rawTime);
	//gmtime_s(realTime, &rawTime);
}
