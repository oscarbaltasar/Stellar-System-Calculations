#pragma once

class User {
private:
	double posX, posY;
	double longitude, latitude;
	long height;

public:
	User(double longitude, double latitude, long height);
	void setPosition(double posX, double posY);
};
