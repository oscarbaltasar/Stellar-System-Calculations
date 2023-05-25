#pragma once
#include "Planet.h"

class User {
private:
	Planet* planet = nullptr;
	SciNumber posXrelative, posYrelative, posZrelative;
	SciNumber posX, posY, posZ;
	float longitude, latitude;
	SciNumber height;

public:
	User(float longitude, float latitude, double height, Planet* planet);
	void calculateRelativePosition();
	void CalculateGlobalPosition();
	std::string toString();

	void CalculateScaledPositions(float* posX, float* posY, float* posZ);
	void addLongitude(float longitude);
	void addLatitude(float latitude);
};
