#pragma once
#include "Satelite.h"
#include "CommonData.h"


//TODO: Añadir inclinación para el eje Z
//TODO: Añadir rotación alrededor de su eje
//TODO: Añadir inclunación de su propio eje por solsticio
class Planet
{
private:

	//General variables
	std::string name;
	Satelite **satelites = nullptr;
	SciNumber posX, posY, posZ;
	SciNumber radiusToCenter;
	SciNumber radius;
	long orbitInclination;				//The inclination of the orbit, relative to other planet, In Degrees
	long axisInclination;				//The inclination of the planet's axis, relative to the sun, In Degrees
	long orbitPeriod;					//How long it takes for the planet to do a full rotation around the Sun, In seconds
	long axisPeriod;					//How long it takes for the planet to do a full rotation around itselft, In seconds

	//Initial positions
	long orbitInclinationNodePosition;	//The positions of the orbit's nodes where the nodes coincide with the relative planet, In seconds
	long upperSolstice;					//The moment in the period when the upper hemisphere and the planet's axis are facing directly to the star, In seconds
	long initialperiodPosition;			//In seconds, assume x = r, y = 0 if value is 0

public:
	Planet(std::string name, double radiusToCenter, int radiusToCenter_SciPow, double radius, int radius_SciPow, long orbitInclination, long axisInclination, long orbitPeriod, long axisPeriod, long orbitInclinationNodePosition = 0, long upperSolstice = 0, long initialperiodPosition = 0);
	void CalculateGlobalPosition(long time);
	void CalculateSatelitesPositions(long time);
	void AddSatelite(Satelite* satelite);
	std::string toString();
	SciNumber getPosX();
	SciNumber getPosY();
	SciNumber getRadius();
};