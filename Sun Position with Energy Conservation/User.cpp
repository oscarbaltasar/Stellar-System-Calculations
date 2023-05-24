#include "User.h"

User::User(float longitude, float latitude, double height, Planet* planet)
{
	posXrelative.number = 0;
	posXrelative.number_SciPow = 0;
	posYrelative.number = 0;
	posYrelative.number_SciPow = 0;
	posZrelative.number = 0;
	posZrelative.number_SciPow = 0;
	posX.number = 0;
	posX.number_SciPow = 0;
	posY.number = 0;
	posY.number_SciPow = 0;
	posZ.number = 0;
	posZ.number_SciPow = 0;
	this->longitude = longitude;
	this->latitude = latitude;
	this->height.number = height;
	CommonData::FixSciNumber(&this->height);
	this->planet = planet;
}

//TODO: tener en cuenta la rotación de los planetas
void User::calculateRelativePosition()
{

	SciNumber sphereRadius = CommonData::AddSciNumber(height, planet->getRadius());
	float sphereLatitude = latitude;
	float sphereLongitude = longitude;

	//Calculate in which hemisphere the user is and it's latitude
	bool userIsInUpperHemisphere = true;
	if (latitude < 0) {
		sphereLatitude *= -1;
		userIsInUpperHemisphere = false;
	}
	sphereLatitude = 90 - sphereLatitude;

	//Calculate in which quadrant the user is (0-3, counter clockwise) and it's longitude
	int quadrantUserisIn = 0; 
	bool mirrorUserQuadrant = false;
	if (longitude < 0) {
		sphereLongitude *= -1;
		mirrorUserQuadrant = true;
	}
	if (sphereLongitude > 90) {
		quadrantUserisIn = 1;
		sphereLongitude -= 90;
	}
	if (mirrorUserQuadrant) quadrantUserisIn = 3 - quadrantUserisIn;

	//Calculate positions assuming planet isn't inclined and it's the moment 0 of the day
	CommonData::CalculatePositionOnSphere(sphereLatitude, sphereLongitude, &sphereRadius, userIsInUpperHemisphere, quadrantUserisIn, &posXrelative, &posYrelative, &posZrelative);

	//Add rotation from axis rotation via Rodrigues: N = (0, 0, 1)
	SciNumber normalX, normalY, normalZ;
	normalX.number = 0;
	normalX.number_SciPow = posXrelative.number_SciPow;
	normalY.number = 0;
	normalY.number_SciPow = posYrelative.number_SciPow;
	normalZ.number = 1;
	normalZ.number_SciPow = posZrelative.number_SciPow;
	float axisRotation = planet->getCurrentAxisRotation() * 2 * PI;
	CommonData::RotatePositionOnSphereViaRodrigues(axisRotation, posXrelative, posYrelative, posZrelative, normalX, normalY, normalZ, &posXrelative, &posYrelative, &posZrelative);
	
	//Add rotation from axis inclination via Rodrigues: N = (0, 1, 0)
	normalX.number = 0;
	normalX.number_SciPow = posXrelative.number_SciPow;
	normalY.number = 1;
	normalY.number_SciPow = posYrelative.number_SciPow;
	normalZ.number = 0;
	normalZ.number_SciPow = posZrelative.number_SciPow;
	float axisInclination = planet->getAxisInclination() * PI / 180;
	CommonData::RotatePositionOnSphereViaRodrigues(axisInclination, posXrelative, posYrelative, posZrelative, normalX, normalY, normalZ, &posXrelative, &posYrelative, &posZrelative);




}

//TODO: calcular con posición Z de los planetas
//TODO: calcular inclinación de los planetas
void User::CalculateGlobalPosition()
{
	posX = CommonData::AddSciNumber(posXrelative, planet->getPosX());
	posY = CommonData::AddSciNumber(posYrelative, planet->getPosY());
	posZ = CommonData::AddSciNumber(posZrelative, planet->getPosZ());
}

std::string User::toString()
{
	std::string res = "User:\n";
	res += "Relative Position:\t" + std::to_string(posXrelative.number) + "*10^" + std::to_string(posXrelative.number_SciPow) + "\t" + std::to_string(posYrelative.number) + "*10^" + std::to_string(posYrelative.number_SciPow) + "\t" + std::to_string(posZrelative.number) + "*10^" + std::to_string(posZrelative.number_SciPow) + + "\n";
	res += "Global Position:\t" + std::to_string(posX.number) + "*10^" + std::to_string(posX.number_SciPow) + "\t" + std::to_string(posY.number) + "*10^" + std::to_string(posY.number_SciPow) + "\t" + std::to_string(posZ.number) + "*10^" + std::to_string(posZ.number_SciPow) + "\n";
	return res;
}
