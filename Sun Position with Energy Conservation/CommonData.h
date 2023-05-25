#pragma once
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

#define EarthPeriod 31558118.4
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
	static inline int lowestExponent;
	static void FixSciNumber(SciNumber *number);
	static SciNumber AddSciNumber(SciNumber a, SciNumber b);
	static SciNumber AddSciNumber(SciNumber a, float b);
	static SciNumber MinusSciNumber(SciNumber a, SciNumber b);
	static SciNumber MultiplySciNumber(SciNumber a, SciNumber b);
	static SciNumber MultiplySciNumber(SciNumber a, float b);
	static void CalculatePositionOnSphere(float latitude, float longitude, SciNumber *sphereRadius, bool latitudeHemisphere, int longitudeQuadrant, SciNumber *posX, SciNumber *posY, SciNumber *posZ);	//Given latitude and longitude calculate positions
	static void RotatePositionOnSphereViaRodrigues(float angle, SciNumber vectorVx, SciNumber vectorVy, SciNumber vectorVz, SciNumber vectorKx, SciNumber vectorKy, SciNumber vectorKz, SciNumber* resultVx, SciNumber* resultVy, SciNumber* resultVz);	//Given latitude and longitude calculate positions
	static void CalculateSciNumberVectorialProduct(SciNumber vectorAx, SciNumber vectorAy, SciNumber vectorAz, SciNumber vectorBx, SciNumber vectorBy, SciNumber vectorBz, SciNumber* resultVx, SciNumber* resultVy, SciNumber* resultVz);
	static void CalculateSciNumberScalarProduct(SciNumber vectorAx, SciNumber vectorAy, SciNumber vectorAz, SciNumber vectorBx, SciNumber vectorBy, SciNumber vectorBz, SciNumber* resultVx, SciNumber* resultVy, SciNumber* resultVz);

private:
	time_t rawTime;
};