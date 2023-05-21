#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <string>
#include <string_view>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <time.h>
#include <chrono>
#include <iomanip>
#include <thread>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

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

typedef struct {
	double number;
	int number_SciPow;
}SciNumber;

class CommonData
{
public:
	
	CommonData();
	~CommonData();
	void updateTime();
	static inline tm* realTime;
	static void FixSciNumber(SciNumber *number);
	static SciNumber AddSciNumber(SciNumber a, SciNumber b);

private:
	time_t rawTime;
};