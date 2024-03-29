#pragma once
#include "CommonData.h"

class Satelite {
private:
	//General variables
	std::string name;
	SciNumber posXrelative, posYrelative, posZrelative;
	SciNumber posX, posY, posZ;
	SciNumber radiusToCenter;
	SciNumber radius;
	float orbitInclination;				//The inclination of the orbit, relative to other GLOBAL planet, In Degrees
	float axisInclination;				//The inclination of the satelite's axis, relative to the Sun, In Degrees
	float orbitPeriod;					//How float it takes for the satelite to do a full rotation around the Planet, In seconds
	float axisPeriod;					//How float it takes for the satelite to do a full rotation around itselft, In seconds
	float currentAxisRotation;			//Current moment of the day (0 - 1)

	//Initial positions
	float orbitInclinationNodePosition;	//The positions of the orbit's nodes where the nodes coincide with the relative GLOBAL planet, In seconds
	float upperSolstice;					//The moment in the period when the upper hemisphere and the planet's axis are facing directly to the sun, In seconds
	float initialperiodPosition;			//In seconds, assume x = r, y = 0 if value is 0
public:
	Satelite(std::string name, double radiusToCenter, int radiusToCenter_SciPow, double radius, int radius_SciPow, float orbitInclination, float axisInclination, float orbitPeriod, float axisPeriod, float orbitInclinationNodePosition = 0, float upperSolstice = 0, float initialperiodPosition = 0);
	void CalculateRelativePosition(float time);
	void CalculateGlobalPosition(SciNumber posXPlanet, SciNumber posYPlanet, SciNumber posZPlanet);
	void CalculateCurrentAxisRotation(float time);
	std::string toString();
	SciNumber getRadius();
	float getAxisInclination();
	float getCurrentAxisRotation();

	void CalculateScaledPositions(float* posX, float* posY, float* posZ);
	double CalculateScaledRadius();
};