#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <string_view>
#include <iostream>
#include <stdio.h>
#include <math.h> 
#include <time.h>
#include <chrono>
#include <iomanip>
#include <format>
#include <thread>

#define PI 3.14159265358979323846

#define EarthPeriod 365.256
#define SecondsinDay 86400
#define EarthInclination 23.44

#define SuntoEarthDistance 149.600																				//imprecisión orbita circular
#define Power_SuntoEarthDistance 6				//Millones de kilometros
#define EarthRadius 6.378																					
#define Power_EarthRadius 3						//Miles de kilometros

#define Longitude -4.064501728800064
#define Latitude 40.71010524106721
//#define Longitude 0
//#define Latitude 0
#define Height 1091								
#define Power_Height -3							//Unidades de kilometros

class GlobalData
{
public:
	
	GlobalData();
	~GlobalData();
	void updateTime();
	static struct tm* realTime;

private:
	time_t rawTime;
};