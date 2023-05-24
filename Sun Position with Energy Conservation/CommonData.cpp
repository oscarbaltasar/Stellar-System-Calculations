#include "CommonData.h"

CommonData::CommonData()
{
	realTime = new tm();
}

CommonData::~CommonData()
{
}

void CommonData::updateTime()
{
	//time(&rawTime);
	gmtime_s(realTime, &rawTime);
}

void CommonData::FixSciNumber(SciNumber *number)
{
	//std::cout << "Number: " + std::to_string(number->number) + "*10^" + std::to_string(number->number_SciPow);
	if (number->number == 0) {
		number->number_SciPow = 0;
		return;
	}
	bool isNegative = false;
	if (number->number < 0) {
		number->number *= -1;
		isNegative = true;
	}
	while (number->number < 1) {
		number->number *= 10;
		number->number_SciPow -= 1;
	}
	while (number->number >= 10) {
		number->number /= 10;
		number->number_SciPow += 1;
	}
	if (isNegative)
		number->number *= -1;
}

SciNumber CommonData::AddSciNumber(SciNumber a, SciNumber b)
{
	SciNumber res = SciNumber();
	res.number = 0;
	res.number_SciPow = 0;
	if (a.number_SciPow == b.number_SciPow) {
		res.number = a.number + b.number;
		res.number_SciPow = a.number_SciPow;
		
	}
	if (a.number_SciPow > b.number_SciPow) {
		int SciPowRest = a.number_SciPow - b.number_SciPow;
		a.number *= pow(10, SciPowRest);
		res.number = a.number + b.number;
		res.number_SciPow = b.number_SciPow;
	}
	if (b.number_SciPow > a.number_SciPow) {
		int SciPowRest = b.number_SciPow - a.number_SciPow;
		b.number *= pow(10, SciPowRest);
		res.number = a.number + b.number;
		res.number_SciPow = a.number_SciPow;
	}
	FixSciNumber(&res);
	return res;
}

void CommonData::CalculatePositionOnSphere(float latitude, float longitude, SciNumber *sphereRadius, bool latitudeHemisphere, int longitudeQuadrant, SciNumber* posX, SciNumber* posY, SciNumber* posZ)
{
	//Calculate positions as if in quadrant 0, upper hemisphere
	posX->number = sphereRadius->number * sin(latitude * (PI / 180)) * cos(longitude * (PI / 180));
	posX->number_SciPow = sphereRadius->number_SciPow;
	CommonData::FixSciNumber(posX);
	posY->number = sphereRadius->number * sin(latitude * (PI / 180)) * sin(longitude * (PI / 180));
	posY->number_SciPow = sphereRadius->number_SciPow;
	CommonData::FixSciNumber(posY);
	posZ->number = sphereRadius->number * cos(latitude * (PI / 180));
	posZ->number_SciPow = sphereRadius->number_SciPow;
	CommonData::FixSciNumber(posZ);

	//Fix to real values assuming the first meridian is looking away from center at x = max, y = 0
	if (!latitudeHemisphere) posZ->number *= -1;

	switch (longitudeQuadrant) {
	case 0:
		break;
	case 1:
		posX->number *= -1;
		break;
	case 2:
		posX->number *= -1;
		posY->number *= -1;
		break;
	case 3:
		posY->number *= -1;
		break;
	}
}
