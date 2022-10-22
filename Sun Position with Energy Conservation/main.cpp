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



int main(int argc, char** argv);


int main(int argc, char** argv) {
	int i = 0;
	int totalMiliseconds;
	while (true) {
		auto start = std::chrono::high_resolution_clock::now();

		time_t rawtime;
		struct tm* info = new struct tm();
		time(&rawtime);
		gmtime_s(info, &rawtime);
		long double currentDay = info->tm_yday + 1;
		
		long double currentSeconds = ((info->tm_hour) * 3600.0 + info->tm_min * 60.0 + info->tm_sec);
		//long double currentSeconds = (12 * 3600.0 + 28 * 60.0 + i);
		int hora = (int)(currentSeconds / 3600);
		int minutos = (int)(((currentSeconds / 3600) - hora) * 60);
		int segundos = round(((((currentSeconds / 3600) - hora) * 60) - minutos) * 60);
		printf("La hora es: %d:%d:%d\n", hora, minutos, segundos);
		printf("- Dias hasta hoy: %Lf\n", currentDay);
		//long double anyoBisiesto = (info->tm_year % 4);
		//anyoBisiesto = anyoBisiesto / 4;


		long double currentPercentage = (currentDay-1 + (currentSeconds / SecondsinDay)) / EarthPeriod;
		//anyoBisiesto = anyoBisiesto + currentPercentage / 4;
		//currentPercentage = currentPercentage + anyoBisiesto / EarthPeriod;
		currentSeconds = currentSeconds + (currentPercentage * 24 * 3600);
		

		//printf("- Porcentage de Bisiesto: %Lf\n", anyoBisiesto);
		long double currentRadians = currentPercentage * 2 * PI;
		//long double currentRadians = 0;
		long double earth_X;
		long double earth_Y;
		printf("- Porcentage de la longitud: %Lf\n", currentPercentage);
		if (currentPercentage < 0.25) {
			printf("   Primer Cuadrante\n");
			earth_X = cos(currentRadians) * (SuntoEarthDistance * pow(10, Power_SuntoEarthDistance));
			earth_Y = sin(currentRadians) * (SuntoEarthDistance * pow(10, Power_SuntoEarthDistance));
		}
		else if (currentPercentage < 0.5) {
			printf("   Segundo Cuadrante\n");
			earth_X = -cos(currentRadians) * (SuntoEarthDistance * pow(10, Power_SuntoEarthDistance));
			earth_Y = sin(currentRadians) * (SuntoEarthDistance * pow(10, Power_SuntoEarthDistance));
		}
		else if (currentPercentage < 0.75) {
			printf("   Tercer Cuadrante\n");
			earth_X = -cos(currentRadians) * (SuntoEarthDistance * pow(10, Power_SuntoEarthDistance));
			earth_Y = -sin(currentRadians) * (SuntoEarthDistance * pow(10, Power_SuntoEarthDistance));
		}
		else {
			printf("   Cuarto Cuadrante\n");
			earth_X = cos(currentRadians) * (SuntoEarthDistance * pow(10, Power_SuntoEarthDistance));
			earth_Y = -sin(currentRadians) * (SuntoEarthDistance * pow(10, Power_SuntoEarthDistance));
		}

		long double earth_Z = 0;

		long double earthRadiusinMeters = EarthRadius * pow(10, Power_EarthRadius) + (Height * pow(10, Power_Height));

		long double userLongidute = 0;
		if (currentSeconds <= SecondsinDay / 2) {
			userLongidute = Longitude + (currentSeconds / SecondsinDay) * 360;
		}
		else {
			userLongidute = Longitude - (360 - (currentSeconds / SecondsinDay) * 360);
		}
		//Ignorando altitud
		long double userLatitude = Latitude;
		//userLatitude = userLatitude - EarthInclination * cos(userLongidute * (PI / 180));			//Intentado calcular angulo de la tierra
		userLatitude = 90 - userLatitude;
		userLatitude = userLatitude + EarthInclination * sin((PI / 360) * (currentDay - 80));
		printf("- Longitud Virtual:\t%Lf,\t Latitud Virtual:\t%Lf\n", Longitude, Latitude);
		printf("- Longitud Real:\t%Lf,\t Latitud Real:  \t%Lf\n", userLongidute, userLatitude);
		long double user_X = earthRadiusinMeters * sin(userLatitude * (PI / 180)) * cos(userLongidute * (PI / 180));
		long double user_Y = earthRadiusinMeters * sin(userLatitude * (PI / 180)) * sin(userLongidute * (PI / 180));
		long double user_Z = earthRadiusinMeters * cos(userLatitude * (PI / 180));

		printf("- Coordenadas Tierra:\t\t\t X = %Lf\t, Y = %Lf\t, Z = %Lf\n", earth_X, earth_Y, earth_Z);
		printf("- Posicion Usuario relativa a la Tierra: X = %Lf\t, Y = %Lf\t, Z = %Lf\n", user_X, user_Y, user_Z);

		user_X = user_X + earth_X;
		user_Y = user_Y + earth_Y;
		user_Z = user_Z + earth_Z;

		printf("- Position Usuario real:\t\t X = %Lf\t, Y = %Lf\t, Z = %Lf\n", user_X, user_Y, user_Z);

		long double horizonNormalVector_X = user_X - earth_X;
		long double horizonNormalVector_Y = user_Y - earth_Y;
		long double horizonNormalVector_Z = user_Z - earth_Z;
		long double horizonEquationEquals = -(horizonNormalVector_X * -user_X + horizonNormalVector_Y * -user_Y + horizonNormalVector_Z * -user_Z);
		printf("- Ecuacion Plano del horizonte:\t %LfX + %LfY + %LfZ = %Lf\n", horizonNormalVector_X, horizonNormalVector_Y, horizonNormalVector_Z, horizonEquationEquals);


		long double angleBetweenHorizonandSun1 = abs(horizonNormalVector_X * user_X + horizonNormalVector_Y * user_Y + horizonNormalVector_Z * user_Z);
		long double angleBetweenHorizonandSun2 = pow(pow(horizonNormalVector_X, 2) + pow(horizonNormalVector_Y, 2) + pow(horizonNormalVector_Z, 2), 0.5) * pow(pow(user_X, 2) + pow(user_Y, 2) + pow(user_Z, 2), 0.5);
		long double angleBetweenHorizonandSun3 = asin(angleBetweenHorizonandSun1 / angleBetweenHorizonandSun2) * 180 / PI;
		printf("Angulo = %Lf\n", angleBetweenHorizonandSun3);
		i++;
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		printf("Fin del ciclo: %d\tTiempo de ejecucion: %d ms\n", i, duration.count());
		
		printf("\n");
		std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::milliseconds(1000-duration.count()));
	}
}