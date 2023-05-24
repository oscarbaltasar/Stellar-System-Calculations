#pragma once
#include "CommonData.h"

class Satelite {
private:
	//General variables
	std::string name;
	SciNumber posXrelative, posYrelative;
	SciNumber posX, posY;
	SciNumber radiusToCenter;
	SciNumber radius;
	long orbitInclination;				//The inclination of the orbit, relative to other GLOBAL planet, In Degrees
	long axisInclination;				//The inclination of the satelite's axis, relative to the Sun, In Degrees
	long orbitPeriod;					//How long it takes for the satelite to do a full rotation around the Planet, In seconds
	long axisPeriod;					//How long it takes for the satelite to do a full rotation around itselft, In seconds

	//Initial positions
	long orbitInclinationNodePosition;	//The positions of the orbit's nodes where the nodes coincide with the relative GLOBAL planet, In seconds
	long upperSolstice;					//The moment in the period when the upper hemisphere and the planet's axis are facing directly to the sun, In seconds
	long initialperiodPosition;			//In seconds, assume x = r, y = 0 if value is 0
public:
	Satelite(std::string name, double radiusToCenter, int radiusToCenter_SciPow, double radius, int radius_SciPow, long orbitInclination, long axisInclination, long orbitPeriod, long axisPeriod, long orbitInclinationNodePosition = 0, long upperSolstice = 0, long initialperiodPosition = 0);
	void CalculateRelativePosition(long time);
	void CalculateGlobalPosition(SciNumber posXPlanet, SciNumber posYPlanet);
	std::string toString();
	SciNumber getRadius();
};