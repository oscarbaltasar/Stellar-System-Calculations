#include "User.h"

User::User(double longitude, double latitude, long height)
{
	this->longitude = longitude;
	this->latitude = latitude;
	this->height = height;
}

void User::setPosition(double posX, double posY)
{
	this->posX = posX;
	this->posY = posY;
}
