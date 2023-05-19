#pragma once
#include "Planet.h"
#include "SystemCenter.h"
#include "User.h"
#include "CommonData.h"

#define realLifePeriod 365.256
#define realLifeSecondsinDay 86400

class SystemSimulation {
private:
	Planet* planets;
	SystemCenter* systemCenter;
	User* user;

	time_t rawTime;
	static std::tm* realTime;

	void UpdateRealTime();

public:
	SystemSimulation(Planet* planets, SystemCenter* systemCenter, User* user);

	void run();
};