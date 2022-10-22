#include "Planet.h"
#include "CommonData.h"

Planet::Planet(float timeOfYear = -1, float timeOfDay = -1, float totalDaysinYear = 365.25, float dayDuration = 24, float hourDuration = 60, float minuteDuration = 60)
{
	this->dayDuration = dayDuration;
	this->hourDuration = hourDuration;
	this->minuteDuration = minuteDuration;
	this->totalDaysinYear = totalDaysinYear;
	if (timeOfDay <= -1)
		this->timeOfDay = CoordinateDayWithEarth();
	else
		this->timeOfDay = timeOfDay;
	if (timeOfYear <= -1)
		this->timeOfYear = CoordinateYearWithEarth();
	else
		this->timeOfYear = timeOfYear;

	timeOfDaywithLag = this->timeOfDay + this->timeOfYear;
	timeOfYearinRadians = this->timeOfYear * 2 * PI;


}

Planet::~Planet()
{
}

//Calculating each second, might be changed later
long double Planet::CurrentTimeplusSeconds(float seconds)
{
	long double planet_Time = timeOfDay * dayDuration * hourDuration * minuteDuration + seconds; //Calculate in seconds the moment of the day

	//Recalculate the moment of the planet for next operations
	float newTimeOfDay = planet_Time / (dayDuration * hourDuration * minuteDuration); 
	timeOfDay = newTimeOfDay;
	timeOfYear = (totalDaysinYear - 1 + timeOfDay) / EarthPeriod;
	timeOfDaywithLag = this->timeOfDay + this->timeOfYear;
	timeOfYearinRadians = this->timeOfYear * 2 * PI;
	
	return planet_Time; //return current seconds
}


//We calculate the moment of the day in % for the Earth and return it
float Planet::CoordinateDayWithEarth()
{
	struct tm* realTime = GlobalData::realTime;
	long double timeonEarth = ((realTime->tm_hour) * 3600.0 + realTime->tm_min * 60.0 + realTime->tm_sec);
	return timeonEarth / SecondsinDay;
}


//We calculate the moment of the year in % for the Earth and return it
float Planet::CoordinateYearWithEarth()
{
	float year_Percentage = (totalDaysinYear - 1 + timeOfDay) / EarthPeriod;
	return year_Percentage;
}
