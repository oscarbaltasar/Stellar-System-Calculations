#pragma once
#include "Satelite.h"
#include "CommonData.h"


//TODO: Añadir inclinación para el eje Z
//TODO: Añadir rotación alrededor de su eje
//TODO: Añadir inclunación de su propio eje por solsticio
class Planet
{
private:
	std::string name;
	Satelite **satelites = nullptr;
	SciNumber posX, posY;
	SciNumber radiusToCenter;
	SciNumber radius;
	long inclination;
	long upperSolstice;			//the moment in the period when the upper hemisphere is facing directly to the star
	long period;				//In seconds
	long initialperiodPosition;	//In seconds, assume x = r, y = 0 if value is 0

public:
	Planet(std::string name, double radiusToCenter, int radiusToCenter_SciPow, double radius, int radius_SciPow, long inclination, long period, long upperSolstice = 0, long initialperiodPosition = 0);
	void CalculateGlobalPosition(long time);
	void CalculateSatelitesPositions(long time);
	void AddSatelite(Satelite* satelite);
	std::string toString();
	SciNumber getPosX();
	SciNumber getPosY();
	SciNumber getRadius();
};