#pragma once
#include "Sun.h"

class SystemCenter {
private:
	Sun sun;
	double posX, posY;

public:
	SystemCenter(double posX, double posY);
};