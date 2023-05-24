#include "Satelite.h"

Satelite::Satelite(std::string name, double radiusToCenter, int radiusToCenter_SciPow, double radius, int radius_SciPow, float orbitInclination, float axisInclination, float orbitPeriod, float axisPeriod, float orbitInclinationNodePosition, float upperSolstice, float initialperiodPosition)
{
	this->name = name;
	posXrelative.number = radius;
	posXrelative.number_SciPow = radiusToCenter_SciPow;
	CommonData::FixSciNumber(&posXrelative);
	posYrelative.number = 0;
	posYrelative.number_SciPow = 0;
	CommonData::FixSciNumber(&posYrelative);
	posZrelative.number = 0;
	posZrelative.number_SciPow = 0;
	CommonData::FixSciNumber(&posZrelative);
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

void Satelite::CalculateRelativePosition(float time)
{
	//TODO: arreglar truncamiento int
	float currentPeriodPosition = ((int)(time + initialperiodPosition) % (int)orbitPeriod) / orbitPeriod;
	float periodToAngle = currentPeriodPosition * (2 * PI);
	if (orbitInclination == 0) { //If no inclination, calculate as simple circle
		posXrelative = CommonData::MultiplySciNumber(radiusToCenter, cos(periodToAngle));
		posYrelative = CommonData::MultiplySciNumber(radiusToCenter, sin(periodToAngle));
	}
	else {						//If inclinated, calculate as an ellipse and a line
		//TODO: asuming inclination nodes are: 0 and it's oposite

		//if we cast the orbit to the plane XY we obtain an ellipse
		//BiggerSphere
		posXrelative = CommonData::MultiplySciNumber(radiusToCenter, cos(periodToAngle));
		//SmallerSphere
		SciNumber smallSphereRadius;
		smallSphereRadius = CommonData::MultiplySciNumber(radiusToCenter, cos(orbitInclination * PI / 180));
		posYrelative = CommonData::MultiplySciNumber(smallSphereRadius, sin(periodToAngle));

		//If we cast the orbit to the ZY plane we obtain a line
		SciNumber lineMaxRange;
		lineMaxRange = CommonData::MultiplySciNumber(radiusToCenter, sin(periodToAngle));
		posZrelative = CommonData::MultiplySciNumber(lineMaxRange, sin(orbitInclination * PI / 180));
	}
}

void Satelite::CalculateGlobalPosition(SciNumber posXPlanet, SciNumber posYPlanet, SciNumber posZPlanet)
{
	posX = CommonData::AddSciNumber(posXrelative, posXPlanet);
	posY = CommonData::AddSciNumber(posYrelative, posYPlanet);
	posZ = CommonData::AddSciNumber(posZrelative, posZPlanet);
}

void Satelite::CalculateCurrentAxisRotation(float time)
{
	if (axisPeriod == 0) { currentAxisRotation = 0; return; }
	currentAxisRotation = ((int)time % (int)axisPeriod) / axisPeriod;
}

std::string Satelite::toString()
{
	std::string res = "Name:\t" + name + "\n";
	res += "Relative Position:\t" + std::to_string(posXrelative.number) + "*10^" + std::to_string(posXrelative.number_SciPow) + "\t" + std::to_string(posYrelative.number) + "*10^" + std::to_string(posYrelative.number_SciPow) + "\t" + std::to_string(posZrelative.number) + "*10^" + std::to_string(posZrelative.number_SciPow) + "\n";
	res += "Global Position:\t" + std::to_string(posX.number) + "*10^" + std::to_string(posX.number_SciPow) + "\t" + std::to_string(posY.number) + "*10^" + std::to_string(posY.number_SciPow) + "\t" + std::to_string(posZ.number) + "*10^" + std::to_string(posZ.number_SciPow) + "\n";
	res += "Radius:\t" + std::to_string(radius.number) + "*10^" + std::to_string(radius.number_SciPow) + "\n";
	res += "Orbit Radius:\t" + std::to_string(radiusToCenter.number) + "*10^" + std::to_string(radiusToCenter.number_SciPow) + "\n";
	return res;
}

SciNumber Satelite::getRadius()
{
	return radius;
}
