#include "Satelite.h"

Satelite::Satelite(std::string name, double radiusToCenter, int radiusToCenter_SciPow, double radius, int radius_SciPow, long orbitInclination, long axisInclination, long orbitPeriod, long axisPeriod, long orbitInclinationNodePosition, long upperSolstice, long initialperiodPosition)
{
	this->name = name;
	posXrelative.number = radius;
	posXrelative.number_SciPow = radiusToCenter_SciPow;
	CommonData::FixSciNumber(&posXrelative);
	posYrelative.number = 0;
	posYrelative.number_SciPow = 0;
	CommonData::FixSciNumber(&posYrelative);
	this->radiusToCenter.number = radiusToCenter;
	this->radiusToCenter.number_SciPow = radiusToCenter_SciPow;
	CommonData::FixSciNumber(&this->radiusToCenter);
	this->radius.number = radius;
	this->radius.number_SciPow = radius_SciPow;
	CommonData::FixSciNumber(&this->radius);
	this->orbitInclination = orbitInclination;
	this->axisInclination = axisInclination;
	this->upperSolstice = upperSolstice;
	this->orbitPeriod = orbitPeriod;
	this->axisPeriod = axisPeriod;
	this->orbitInclinationNodePosition = orbitInclinationNodePosition;
	this->initialperiodPosition = initialperiodPosition;
}

void Satelite::CalculateRelativePosition(long time)
{
	long currentPeriodPosition = ((time + initialperiodPosition) % orbitPeriod) / orbitPeriod;
	long periodToAngle = currentPeriodPosition * (2 * PI);

	posXrelative.number = sin(periodToAngle) * radiusToCenter.number;
	posXrelative.number_SciPow = radiusToCenter.number_SciPow;
	CommonData::FixSciNumber(&posXrelative);

	posYrelative.number = cos(periodToAngle) * radiusToCenter.number;
	posYrelative.number_SciPow = radiusToCenter.number_SciPow;
	CommonData::FixSciNumber(&posYrelative);
}

void Satelite::CalculateGlobalPosition(SciNumber posXPlanet, SciNumber posYPlanet)
{
	posX = CommonData::AddSciNumber(posXrelative, posXPlanet);
	posY = CommonData::AddSciNumber(posYrelative, posYPlanet);
}

std::string Satelite::toString()
{
	std::string res = "Name:\t" + name + "\n";
	res += "Relative Position:\t" + std::to_string(posXrelative.number) + "*10^" + std::to_string(posXrelative.number_SciPow) + "\t" + std::to_string(posYrelative.number) + "*10^" + std::to_string(posYrelative.number_SciPow) + "\n";
	res += "Global Position:\t" + std::to_string(posX.number) + "*10^" + std::to_string(posX.number_SciPow) + "\t" + std::to_string(posY.number) + "*10^" + std::to_string(posY.number_SciPow) + "\n";
	res += "Radius:\t" + std::to_string(radius.number) + "*10^" + std::to_string(radius.number_SciPow) + "\n";
	res += "Orbit Radius:\t" + std::to_string(radiusToCenter.number) + "*10^" + std::to_string(radiusToCenter.number_SciPow) + "\n";
	return res;
}

SciNumber Satelite::getRadius()
{
	return radius;
}
