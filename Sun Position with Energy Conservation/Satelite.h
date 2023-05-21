#pragma once
#include "CommonData.h"

class Satelite {
private:
	std::string name;
	SciNumber posXrelative, posYrelative;
	SciNumber posX, posY;
	SciNumber radiusToCenter;
	SciNumber radius;
	long inclination;
	long upperSolstice;			//the moment in the period when the upper hemisphere is facing directly to the planet
	long period;				//In seconds
	long initialperiodPosition;	//In seconds, assume x = r, y = 0 if value is 0
public:
	Satelite(std::string name, double radiusToCenter, int radiusToCenter_SciPow, double radius, int radius_SciPow, long inclination, long period, long upperSolstice = 0, long initialperiodPosition = 0);
	void CalculateRelativePosition(long time);
	void CalculateGlobalPosition(SciNumber posXPlanet, SciNumber posYPlanet);
	std::string toString();
	SciNumber getRadius();
};