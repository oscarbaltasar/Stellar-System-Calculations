#include "Planet.h"

Planet::Planet(std::string name, double radiusToCenter, int radiusToCenter_SciPow, double radius, int radius_SciPow, long inclination, long period, long initialperiodPosition)
{
	this->name = name;
	posX.number = radius;
	posX.number_SciPow = radiusToCenter_SciPow;
	CommonData::FixSciNumber(&posX);
	posY.number = 0;
	posY.number_SciPow = 0;
	CommonData::FixSciNumber(&posY);
	this->radiusToCenter.number = radiusToCenter;
	this->radiusToCenter.number_SciPow = radiusToCenter_SciPow;
	CommonData::FixSciNumber(&this->radiusToCenter);
	this->radius.number = radius;
	this->radius.number_SciPow = radius_SciPow;
	CommonData::FixSciNumber(&this->radius);
	this->inclination = inclination;
	this->period = period;
	this->initialperiodPosition = initialperiodPosition;
}

void Planet::CalculateGlobalPosition(long time)
{
	long currentPeriodPosition = ((time + initialperiodPosition) % period) / period;
	long periodToAngle = period * (2 * PI);

	posX.number = sin(periodToAngle) * radiusToCenter.number;
	posX.number_SciPow = radiusToCenter.number_SciPow;
	CommonData::FixSciNumber(&posX);

	posY.number = cos(periodToAngle) * radiusToCenter.number;
	posY.number_SciPow = radiusToCenter.number_SciPow;
	CommonData::FixSciNumber(&posY);
}

void Planet::CalculateSatelitesPositions(long time)
{
	if (satelites == nullptr)
		return;
	int numberofSatelites = sizeof(**satelites) / sizeof(Satelite);
	for (int i = 0; i < numberofSatelites; i++) {
		(*satelites)[i].CalculateRelativePosition(time);
		(*satelites)[i].CalculateGlobalPosition(posX, posY);
		std::cout << (*satelites)[i].toString();
	}
}

void Planet::AddSatelite(Satelite* satelite)
{
	int satelitesNumber = sizeof(*satelites) / sizeof(Satelite*) + 1;
	if (satelites == nullptr) satelitesNumber = 1;
	Satelite** buffer;
	buffer = (Satelite**)malloc(satelitesNumber*sizeof(Satelite*));
	if (satelites != nullptr) {
		for (int i = 0; i < satelitesNumber - 1; i++) {
			buffer[i] = satelites[i];
		}
		free(satelites);
	}
	buffer[satelitesNumber - 1] = satelite;
	std::cout << buffer[0]->toString();
	satelites = buffer;
	std::cout << satelites[0]->toString();
}

std::string Planet::toString()
{
	std::string res = "Name:\t" + name + "\n";
	res += "Position:\t" + std::to_string(posX.number) + "*10^" + std::to_string(posX.number_SciPow) + "\t" + std::to_string(posY.number) + "*10^" + std::to_string(posY.number_SciPow) + "\n";
	res += "Radius:\t" + std::to_string(radius.number) + "*10^" + std::to_string(radius.number_SciPow) + "\n";
	res += "Orbit Radius:\t" + std::to_string(radiusToCenter.number) + "*10^" + std::to_string(radiusToCenter.number_SciPow) + "\n";
	return res;
}

SciNumber Planet::getPosX()
{
	return posX;
}

SciNumber Planet::getPosY()
{
	return posY;
}
