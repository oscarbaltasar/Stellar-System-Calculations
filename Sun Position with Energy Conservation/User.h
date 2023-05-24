#pragma once
#include "Planet.h"

class User {
private:
	Planet* planet = nullptr;
	SciNumber posXrelative, posYrelative, posZrelative;
	SciNumber posX, posY, posZ;
	long longitude, latitude;
	SciNumber height;

public:
	User(long longitude, long latitude, double height, Planet* planet);
	void calculateRelativePosition();
	void CalculateGlobalPosition();
	std::string toString();
};
