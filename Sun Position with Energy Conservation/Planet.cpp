#include "Planet.h"

Planet::Planet(std::string name, double radiusToCenter, int radiusToCenter_SciPow, double radius, int radius_SciPow, long orbitInclination, long axisInclination, long period, long axisPeriod, long orbitInclinationNodePosition, long upperSolstice, long initialperiodPosition)
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
	this->orbitInclination = orbitInclination;
	this->axisInclination = axisInclination;
	this->upperSolstice = upperSolstice;
	this->orbitPeriod = period;
	this->orbitInclinationNodePosition = orbitInclinationNodePosition;
	this->initialperiodPosition = initialperiodPosition;
}

//TODO: tener en cuenta cuando pasa un año para que no se acaben las orbitas preventivamente 
//TODO: Calcular posición en Z por rotación de orbita
void Planet::CalculateGlobalPosition(long time)
{
	long currentPeriodPosition = ((time + initialperiodPosition) % orbitPeriod) / orbitPeriod;
	long periodToAngle = currentPeriodPosition * (2 * PI);
	std::cout << std::to_string(time)+" / "+ std::to_string(orbitPeriod) + " = " + std::to_string((long)(time / orbitPeriod)) + "\n";
	if (orbitInclination == 0) { //If no inclination, calculate as simple circle

		posX.number = sin(periodToAngle) * radiusToCenter.number;
		posX.number_SciPow = radiusToCenter.number_SciPow;
		CommonData::FixSciNumber(&posX);

		posY.number = cos(periodToAngle) * radiusToCenter.number;
		posY.number_SciPow = radiusToCenter.number_SciPow;
		CommonData::FixSciNumber(&posY);
	}
	else {						//If inclinated, calculate as an ellipse and a line
		//TODO: asuming inclination nodes are: 0 and it's oposite
		
		//if we cast the orbit to the plane XY we obtain an ellipse
		//BiggerSphere
		posX.number = cos(periodToAngle) * radiusToCenter.number;
		posX.number_SciPow = radiusToCenter.number_SciPow;
		CommonData::FixSciNumber(&posX);
		//SmallerSphere
		SciNumber smallSphereRadius;
		smallSphereRadius.number = cos(orbitInclination * PI / 180) * radiusToCenter.number;
		smallSphereRadius.number_SciPow = radiusToCenter.number_SciPow;
		CommonData::FixSciNumber(&smallSphereRadius);
		posY.number = sin(periodToAngle) * smallSphereRadius.number;
		posY.number_SciPow = smallSphereRadius.number_SciPow;
		CommonData::FixSciNumber(&posY);


		//If we cast the orbit to the ZY plane we obtain a line
		SciNumber lineMaxRange;
		lineMaxRange.number = sin(periodToAngle) * radiusToCenter.number;
		lineMaxRange.number_SciPow = radiusToCenter.number_SciPow;
		CommonData::FixSciNumber(&lineMaxRange);
		posZ.number = sin(orbitInclination * PI / 180) * lineMaxRange.number;
		posZ.number_SciPow = lineMaxRange.number_SciPow;
		CommonData::FixSciNumber(&posZ);


	}
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
	res += "Position:\t" + std::to_string(posX.number) + "*10^" + std::to_string(posX.number_SciPow) + "\t" + std::to_string(posY.number) + "*10^" + std::to_string(posY.number_SciPow) + "\t" + std::to_string(posZ.number) + "*10^" + std::to_string(posZ.number_SciPow) + "\n";
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

SciNumber Planet::getRadius()
{
	return radius;
}