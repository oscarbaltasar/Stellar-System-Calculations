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
	float orbitInclination;				//The inclination of the orbit, relative to other planet, In Degrees
	float axisInclination;				//The inclination of the planet's axis, relative to the sun, In Degrees
	float orbitPeriod;					//How float it takes for the planet to do a full rotation around the Sun, In seconds
	float axisPeriod;					//How float it takes for the planet to do a full rotation around itselft, In seconds
	float currentAxisRotation;			//Current moment of the day (0 - 1)

	//Initial positions
	float orbitInclinationNodePosition;	//The positions of the orbit's nodes where the nodes coincide with the relative planet, In seconds
	float upperSolstice;					//The moment in the period when the upper hemisphere and the planet's axis are facing directly to the star, In seconds
	float initialperiodPosition;			//In seconds, assume x = r, y = 0 if value is 0

public:
	Planet(std::string name, double radiusToCenter, int radiusToCenter_SciPow, double radius, int radius_SciPow, float orbitInclination, float axisInclination, float orbitPeriod, float axisPeriod, float orbitInclinationNodePosition = 0, float upperSolstice = 0, float initialperiodPosition = 0);
	void CalculateGlobalPosition(float time);
	void CalculateCurrentAxisRotation(float time);
	void CalculateSatelitesPositions(float time);
	void AddSatelite(Satelite* satelite);
	std::string toString();
	SciNumber getPosX();
	SciNumber getPosY();
	SciNumber getPosZ();
	SciNumber getRadius();
	float getAxisInclination();
	float getCurrentAxisRotation();
	

	void CalculateScaledPositions(float* posX, float* posY, float* posZ);
	double CalculateScaledRadius();
};