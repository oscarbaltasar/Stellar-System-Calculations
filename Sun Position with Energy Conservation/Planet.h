#pragma once

class Planet
{
public:
	Planet(float timeOfYear = -1, float timeOfDay = -1, float totalDaysinYear = 365.25, float dayDuration = 24, float hourDuration = 60, float minuteDuration = 60);
	~Planet();
	long double CurrentTimeplusSeconds(float seconds);

private:
	long double planet_X;
	long double planet_Y;
	float dayDuration; //In Hours
	float hourDuration; //In Minutes
	float minuteDuration; //In Seconds
	float totalDaysinYear;
	int currentDay;
	float timeOfDay; //Current moment of the day in %
	float timeOfDaywithLag; //Current "real" moment of the day in % while taking into account the gap created by the planet's rotation during the year
	float timeOfYear; //Current moment of the year in %
	float timeOfYearinRadians; //Current moment of the year in Radians
	
	float CoordinateDayWithEarth();
	float CoordinateYearWithEarth();
};