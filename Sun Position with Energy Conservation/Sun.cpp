#include "Sun.h"

Sun::Sun(double radius, int radius_SciPow)
{
	this->radius.number = radius;
	this->radius.number_SciPow = radius_SciPow;
}

double Sun::CalculateScaledRadius()
{
	int resExponent = this->radius.number_SciPow - CommonData::lowestExponent;
	std::cout << "Sun realer Scale: " + std::to_string(this->radius.number) + "*10^" + std::to_string(this->radius.number_SciPow - CommonData::lowestExponent) + "\n";
	double res = this->radius.number * pow(10, resExponent);
	std::cout << "Sun real Scale: " + std::to_string(res) + "\n\n\n\n\n\n\n\n";
	return res;
}
