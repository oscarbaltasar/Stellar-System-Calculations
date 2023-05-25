#pragma once
#include "CommonData.h"

class Sun {
private:

	//General variables
	SciNumber radius;

public:
	Sun(double radius, int radius_SciPow);

	double CalculateScaledRadius();
};