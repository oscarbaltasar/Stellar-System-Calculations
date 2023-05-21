#include "User.h"

User::User(double longitude, double latitude, double height, Planet* planet)
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

void User::calculateRelativePosition()
{

	SciNumber sphereRadius = CommonData::AddSciNumber(height, planet->getRadius());
	long sphereLatitude = latitude;
	long sphereLongitude = longitude;

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

	//Calculate positions as if in quadrant 0, upper hemisphere
	posXrelative.number = sphereRadius.number * sin(sphereLatitude * (PI / 180)) * cos(sphereLongitude * (PI / 180));
	posXrelative.number_SciPow = sphereRadius.number_SciPow;
	CommonData::FixSciNumber(&posXrelative);
	posYrelative.number = sphereRadius.number * sin(sphereLatitude * (PI / 180)) * sin(sphereLongitude * (PI / 180));
	posYrelative.number_SciPow = sphereRadius.number_SciPow;
	CommonData::FixSciNumber(&posYrelative);
	posZrelative.number = sphereRadius.number * cos(sphereLatitude * (PI / 180));
	posZrelative.number_SciPow = sphereRadius.number_SciPow;
	CommonData::FixSciNumber(&posZrelative);

	//Fix to real values assuming the first meridian is looking away from center at x = max, y = 0
	if (!userIsInUpperHemisphere) posZrelative.number *= -1;

	switch (quadrantUserisIn) {
	case 0:
		break;
	case 1:
		posXrelative.number *= -1;
		break;
	case 2:
		posXrelative.number *= -1;
		posYrelative.number *= -1;
		break;
	case 3:
		posYrelative.number *= -1;
		break;
	}
}

//TODO: calcular con posición Z de los planetas
//TODO: calcular inclinación de los planetas
void User::CalculateGlobalPosition()
{
	posX = CommonData::AddSciNumber(posXrelative, planet->getPosX());
	posY = CommonData::AddSciNumber(posYrelative, planet->getPosY());
	posZ = posZrelative;
}

std::string User::toString()
{
	std::string res = "User:\n";
	res += "Relative Position:\t" + std::to_string(posXrelative.number) + "*10^" + std::to_string(posXrelative.number_SciPow) + "\t" + std::to_string(posYrelative.number) + "*10^" + std::to_string(posYrelative.number_SciPow) + "\t" + std::to_string(posZrelative.number) + "*10^" + std::to_string(posZrelative.number_SciPow) + + "\n";
	res += "Global Position:\t" + std::to_string(posX.number) + "*10^" + std::to_string(posX.number_SciPow) + "\t" + std::to_string(posY.number) + "*10^" + std::to_string(posY.number_SciPow) + "\t" + std::to_string(posZ.number) + "*10^" + std::to_string(posZ.number_SciPow) + "\n";
	return res;
}
