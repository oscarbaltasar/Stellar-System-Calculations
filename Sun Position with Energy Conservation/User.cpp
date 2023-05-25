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
	sphereLatitude -= 90;
	sphereLatitude *= -1;
	float sphereLongitude = longitude;
	

	//Calculate positions assuming planet isn't inclined and it's the moment 0 of the day
	CommonData::CalculatePositionOnSphere(sphereLatitude, sphereLongitude, &sphereRadius, 1, -1, &posXrelative, &posYrelative, &posZrelative);

	//Add rotation from axis rotation via Rodrigues: N = (0, 0, 1)
	SciNumber normalX, normalY, normalZ;
	normalX.number = 0;
	normalX.number_SciPow = posXrelative.number_SciPow;
	normalY.number = 0;
	normalY.number_SciPow = posYrelative.number_SciPow;
	normalZ.number = 1;
	normalZ.number_SciPow = posZrelative.number_SciPow;
	float axisRotation = planet->getCurrentAxisRotation() * 2 * PI;
	//CommonData::RotatePositionOnSphereViaRodrigues(axisRotation, posXrelative, posYrelative, posZrelative, normalX, normalY, normalZ, &posXrelative, &posYrelative, &posZrelative);
	
	//Add rotation from axis inclination via Rodrigues: N = (0, 1, 0)
	normalX.number = 0;
	normalX.number_SciPow = posXrelative.number_SciPow;
	normalY.number = 1;
	normalY.number_SciPow = posYrelative.number_SciPow;
	normalZ.number = 0;
	normalZ.number_SciPow = posZrelative.number_SciPow;
	float axisInclination = planet->getAxisInclination() * PI / 180;
	//CommonData::RotatePositionOnSphereViaRodrigues(axisInclination, posXrelative, posYrelative, posZrelative, normalX, normalY, normalZ, &posXrelative, &posYrelative, &posZrelative);




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
	res += "Longitude and Latitude:\t" + std::to_string(longitude) + "\t" + std::to_string(latitude) + "\n";
	return res;
}

void User::CalculateScaledPositions(float* posX, float* posY, float* posZ)
{
	int posXexponent = this->posX.number_SciPow - CommonData::lowestExponent;
	*posX = (float)(this->posX.number * pow(10, posXexponent));

	int posYexponent = this->posY.number_SciPow - CommonData::lowestExponent;
	*posY = (float)(this->posY.number * pow(10, posYexponent));

	int posZexponent = this->posZ.number_SciPow - CommonData::lowestExponent;
	*posZ = (float)(this->posZ.number * pow(10, posZexponent));
}

void User::addLongitude(float longitude)
{
	this->longitude += longitude;
	if (this->longitude > 180) this->longitude -= 360;
	if (this->longitude < -180) this->longitude += 360;
}

void User::addLatitude(float latitude)
{
	this->latitude += latitude;
	if (this->latitude > 90) this->latitude = 90;
	if (this->latitude < -90) this->latitude = -90;
}
