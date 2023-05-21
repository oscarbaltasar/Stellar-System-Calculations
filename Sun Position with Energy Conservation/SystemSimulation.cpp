#include "SystemSimulation.h"

SystemSimulation::SystemSimulation(Planet* planets, SystemCenter* systemCenter, User* user)
{
	realTime = new tm();
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
		int lastSecond = realTime->tm_sec;
		this->UpdateRealTime();
		if (lastSecond == realTime->tm_sec) continue; //only once each second
		std::cout << "Son las: " + std::to_string(realTime->tm_hour) + ":" + std::to_string(realTime->tm_min) + ":" + std::to_string(realTime->tm_sec) + "\n";

		//Calculate each planet, satelite and user position
		int numberofPlanets = sizeof(*planets) / sizeof(Planet);
		for (int i = 0; i < numberofPlanets; i++) {
			planets[i].CalculateGlobalPosition(DebugTime);
			std::cout << planets[i].toString();
			planets[i].CalculateSatelitesPositions(DebugTime);
			
			user->calculateRelativePosition();
			user->CalculateGlobalPosition();
			std::cout << user->toString();
			
		}
		std::cout << "\n\n\n";
	}
}

void SystemSimulation::UpdateRealTime() {
	time(&rawTime);
	gmtime_s(realTime, &rawTime);
}
