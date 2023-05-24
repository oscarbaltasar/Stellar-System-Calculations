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

SciNumber CommonData::MinusSciNumber(SciNumber a, SciNumber b)
{
	SciNumber res = SciNumber();
	res.number = 0;
	res.number_SciPow = 0;
	if (a.number_SciPow == b.number_SciPow) {
		res.number = a.number - b.number;
		res.number_SciPow = a.number_SciPow;

	}
	if (a.number_SciPow > b.number_SciPow) {
		int SciPowRest = a.number_SciPow - b.number_SciPow;
		a.number *= pow(10, SciPowRest);
		res.number = a.number - b.number;
		res.number_SciPow = b.number_SciPow;
	}
	if (b.number_SciPow > a.number_SciPow) {
		int SciPowRest = b.number_SciPow - a.number_SciPow;
		b.number *= pow(10, SciPowRest);
		res.number = a.number - b.number;
		res.number_SciPow = a.number_SciPow;
	}
	FixSciNumber(&res);
	return res;
}

SciNumber CommonData::MultiplySciNumber(SciNumber a, SciNumber b) 
{
	SciNumber res = SciNumber();
	res.number = 0;
	res.number_SciPow = 0;
	if (a.number == 0 || b.number == 0) return res;
	if (a.number_SciPow == b.number_SciPow) {
		res.number = a.number * b.number;
		res.number_SciPow = a.number_SciPow;
	}
	if (a.number_SciPow > b.number_SciPow) {
		int SciPowRest = a.number_SciPow - b.number_SciPow;
		a.number *= pow(10, SciPowRest);
		res.number = a.number * b.number;
		res.number_SciPow = b.number_SciPow;
	}
	if (b.number_SciPow > a.number_SciPow) {
		int SciPowRest = b.number_SciPow - a.number_SciPow;
		b.number *= pow(10, SciPowRest);
		res.number = a.number * b.number;
		res.number_SciPow = a.number_SciPow;
	}
	FixSciNumber(&res);
	return res;
}

SciNumber CommonData::MultiplySciNumber(SciNumber a, float b)
{
	SciNumber res = SciNumber();
	res.number = 0;
	res.number_SciPow = 0;
	if (a.number == 0 || b == 0) return res;
	res.number = a.number * b;
	res.number_SciPow = a.number_SciPow;
	FixSciNumber(&res);
	return res;
}

void CommonData::CalculatePositionOnSphere(float latitude, float longitude, SciNumber *sphereRadius, bool latitudeHemisphere, int longitudeQuadrant, SciNumber* posX, SciNumber* posY, SciNumber* posZ)
{
	//Calculate positions as if in quadrant 0, upper hemisphere
	*posX = MultiplySciNumber(*sphereRadius, sin(latitude * (PI / 180)) * cos(longitude * (PI / 180)));
	*posY = MultiplySciNumber(*sphereRadius, sin(latitude * (PI / 180)) * sin(longitude * (PI / 180)));
	*posZ = MultiplySciNumber(*sphereRadius, cos(latitude * (PI / 180)));
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

void CommonData::RotatePositionOnSphereViaRodrigues(float angle, SciNumber vectorVx, SciNumber vectorVy, SciNumber vectorVz, SciNumber vectorKx, SciNumber vectorKy, SciNumber vectorKz, SciNumber* resultVx, SciNumber* resultVy, SciNumber* resultVz)
{

	
	SciNumber vectorialProductX, vectorialProductY, vectorialProductZ;
	CommonData::CalculateSciNumberVectorialProduct(vectorKx, vectorKy, vectorKz, vectorVx, vectorVy, vectorVz, &vectorialProductX, &vectorialProductY, &vectorialProductZ);
	SciNumber scalarProductX, scalarProductY, scalarProductZ;
	CommonData::CalculateSciNumberScalarProduct(vectorKx, vectorKy, vectorKz, vectorVx, vectorVy, vectorVz, &scalarProductX, &scalarProductY, &scalarProductZ);
	//std::cout << std::to_string(vectorKz.number) + " * " + std::to_string(vectorVz.number) + "\n";
	//std::cout << std::to_string(MultiplySciNumber(vectorVz, cos(angle)).number) + " + " + std::to_string(MultiplySciNumber(MultiplySciNumber(vectorKz, scalarProductZ), (1 - cos(angle))).number) + "\n";

	// V * cos + (KxV) * sin + K(K·V)(1-cos)
	*resultVx = AddSciNumber(AddSciNumber(MultiplySciNumber(vectorVx, cos(angle)), MultiplySciNumber(vectorialProductX, sin(angle))), MultiplySciNumber(MultiplySciNumber(vectorKx, scalarProductX), (1 - cos(angle))));
	*resultVy = AddSciNumber(AddSciNumber(MultiplySciNumber(vectorVy, cos(angle)), MultiplySciNumber(vectorialProductY, sin(angle))), MultiplySciNumber(MultiplySciNumber(vectorKy, scalarProductY), (1 - cos(angle))));
	*resultVz = AddSciNumber(AddSciNumber(MultiplySciNumber(vectorVz, cos(angle)), MultiplySciNumber(vectorialProductZ, sin(angle))), MultiplySciNumber(MultiplySciNumber(vectorKz, scalarProductZ), (1 - cos(angle))));
}

void CommonData::CalculateSciNumberVectorialProduct(SciNumber vectorAx, SciNumber vectorAy, SciNumber vectorAz, SciNumber vectorBx, SciNumber vectorBy, SciNumber vectorBz, SciNumber *resultVx, SciNumber *resultVy, SciNumber *resultVz)
{
	*resultVx = MinusSciNumber(MultiplySciNumber(vectorAy, vectorBz),MultiplySciNumber(vectorAz, vectorBy));
	*resultVy = MinusSciNumber(MultiplySciNumber(vectorAz, vectorBx),MultiplySciNumber(vectorAx, vectorBz));
	*resultVz = MinusSciNumber(MultiplySciNumber(vectorAx, vectorBy),MultiplySciNumber(vectorAy, vectorBx));
}

void CommonData::CalculateSciNumberScalarProduct(SciNumber vectorAx, SciNumber vectorAy, SciNumber vectorAz, SciNumber vectorBx, SciNumber vectorBy, SciNumber vectorBz, SciNumber* resultVx, SciNumber* resultVy, SciNumber* resultVz)
{
	*resultVx = MultiplySciNumber(vectorAx, vectorBx);
	*resultVy = MultiplySciNumber(vectorAy, vectorBy);
	*resultVz = MultiplySciNumber(vectorAz, vectorBz);
}
