#include "Planet.h"

Planet::Planet(std::string name, double radiusToCenter, int radiusToCenter_SciPow, double radius, int radius_SciPow, float orbitInclination, float axisInclination, float period, float axisPeriod, float orbitInclinationNodePosition, float upperSolstice, float initialperiodPosition)
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
	this->axisPeriod = axisPeriod;
	this->orbitInclinationNodePosition = orbitInclinationNodePosition;
	this->initialperiodPosition = initialperiodPosition;
}

//TODO: tener en cuenta cuando pasa un año para que no se acaben las orbitas preventivamente 
//TODO: Calcular posición en Z por rotación de orbita
void Planet::CalculateGlobalPosition(float time)
{
	//TODO: arreglar truncamiento int
	float currentPeriodPosition = ((int)(time + initialperiodPosition) % (int)orbitPeriod) / orbitPeriod;
	float periodToAngle = currentPeriodPosition * (2 * PI);
	if (orbitInclination == 0) { //If no inclination, calculate as simple circle
		posX = CommonData::MultiplySciNumber(radiusToCenter, cos(periodToAngle));
		posY = CommonData::MultiplySciNumber(radiusToCenter, sin(periodToAngle));
	}
	else {						//If inclinated, calculate as an ellipse and a line
		//TODO: asuming inclination nodes are: 0 and it's oposite
		
		//if we cast the orbit to the plane XY we obtain an ellipse
		//BiggerSphere
		posX = CommonData::MultiplySciNumber(radiusToCenter, cos(periodToAngle));
		//SmallerSphere
		SciNumber smallSphereRadius;
		smallSphereRadius = CommonData::MultiplySciNumber(radiusToCenter, cos(orbitInclination * PI / 180));
		posY = CommonData::MultiplySciNumber(smallSphereRadius, sin(periodToAngle));

		//If we cast the orbit to the ZY plane we obtain a line
		SciNumber lineMaxRange;
		lineMaxRange = CommonData::MultiplySciNumber(radiusToCenter, sin(periodToAngle));
		posZ = CommonData::MultiplySciNumber(lineMaxRange, sin(orbitInclination * PI / 180));
	}
}

void Planet::CalculateCurrentAxisRotation(float time)
{
	if (axisPeriod == 0) { currentAxisRotation = 0; return; }
	//(current day progress + current orbit progress) % 1
	currentAxisRotation = (((int)time % (int)axisPeriod) / axisPeriod + ((int)(time + initialperiodPosition) % (int)orbitPeriod) / orbitPeriod);
	if (currentAxisRotation > 1) currentAxisRotation -= 1;
}

void Planet::CalculateSatelitesPositions(float time)
{
	if (satelites == nullptr)
		return;
	int numberofSatelites = sizeof(**satelites) / sizeof(Satelite);
	for (int i = 0; i < numberofSatelites; i++) {
		(*satelites)[i].CalculateRelativePosition(time);
		(*satelites)[i].CalculateGlobalPosition(posX, posY, posZ);
		(*satelites)[i].CalculateCurrentAxisRotation(time);
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

SciNumber Planet::getPosZ()
{
	return posZ;
}

SciNumber Planet::getRadius()
{
	return radius;
}

//Range = (0 - 360) degrees
float Planet::getAxisInclination()
{
	return axisInclination;
}

//Range = (0 - 1) %
float Planet::getCurrentAxisRotation()
{
	return currentAxisRotation;
}
