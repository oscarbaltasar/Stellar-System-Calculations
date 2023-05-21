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
