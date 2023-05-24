#include "SystemSimulation.h"


int main(int argc, char** argv) {
	std::cout << "Iniciando valores\n";
	Satelite* moon = new Satelite("moon",3.844, 6, 1.7374, 3, 5.14, 6.68, 2358720, 2358720,0,0,0);
	Planet* earth = new Planet("earth",1.496, 8, 6.378, 3, 8, 23.44, 31558118.4, 86400,0, 14860800,0);
	earth->AddSatelite(moon);
	SystemCenter sun = SystemCenter(0, 0);
	User* user = new User(-4.064501728800064, 40.71010524106721, 1.091, earth);
	SystemSimulation systemSimulation(earth,&sun,user);

	std::cout << "Iniciando simulacion\n";
	systemSimulation.run();
}


/*
int main(int argc, char** argv) {
	CommonData system_Data;
	int i = 0;
	int totalMiliseconds;
	while (true) {
		auto start = std::chrono::high_resolution_clock::now();
		system_Data.updateTime();

		struct tm* realTime = system_Data.realTime;
		float double earth_Day = realTime->tm_yday + 1;

		Planet earth = Planet();
		
		float double earth_T_Seconds = ((realTime->tm_hour) * 3600.0 + realTime->tm_min * 60.0 + realTime->tm_sec);
		//float double currentSeconds = (12 * 3600.0 + 28 * 60.0 + i);
		int earth_Hour = (int)(earth_T_Seconds / 3600);
		int earth_Minutes = (int)(((earth_T_Seconds / 3600) - earth_Hour) * 60);
		int earth_Seconds = round(((((earth_T_Seconds / 3600) - earth_Hour) * 60) - earth_Minutes) * 60);
		printf("La hora es: %d:%d:%d\n", earth_Hour, earth_Minutes, earth_Seconds);
		printf("- Dias hasta hoy: %Lf\n", earth_Day);
		//float double anyoBisiesto = (info->tm_year % 4);
		//anyoBisiesto = anyoBisiesto / 4;


		float double year_Percentage = (earth_Day-1 + (earth_T_Seconds / SecondsinDay)) / EarthPeriod;
		//anyoBisiesto = anyoBisiesto + currentPercentage / 4;
		//currentPercentage = currentPercentage + anyoBisiesto / EarthPeriod;
		//Desfase del a�o
		earth_T_Seconds = earth_T_Seconds + (year_Percentage * 24 * 3600);
		

		//printf("- Porcentage de Bisiesto: %Lf\n", anyoBisiesto);
		float double year_PercentageRadians = year_Percentage * 2 * PI;
		//float double currentRadians = 0;
		float double planet_X;
		float double planet_Y;
		printf("- Porcentage de la longitud: %Lf\n", year_Percentage);
		if (year_Percentage < 0.25) {
			printf("   Primer Cuadrante\n");
			planet_X = cos(year_PercentageRadians) * (SuntoEarthDistance * pow(10, Power_SuntoEarthDistance));
			planet_Y = sin(year_PercentageRadians) * (SuntoEarthDistance * pow(10, Power_SuntoEarthDistance));
		}
		else if (year_Percentage < 0.5) {
			printf("   Segundo Cuadrante\n");
			planet_X = -cos(year_PercentageRadians) * (SuntoEarthDistance * pow(10, Power_SuntoEarthDistance));
			planet_Y = sin(year_PercentageRadians) * (SuntoEarthDistance * pow(10, Power_SuntoEarthDistance));
		}
		else if (year_Percentage < 0.75) {
			printf("   Tercer Cuadrante\n");
			planet_X = -cos(year_PercentageRadians) * (SuntoEarthDistance * pow(10, Power_SuntoEarthDistance));
			planet_Y = -sin(year_PercentageRadians) * (SuntoEarthDistance * pow(10, Power_SuntoEarthDistance));
		}
		else {
			printf("   Cuarto Cuadrante\n");
			planet_X = cos(year_PercentageRadians) * (SuntoEarthDistance * pow(10, Power_SuntoEarthDistance));
			planet_Y = -sin(year_PercentageRadians) * (SuntoEarthDistance * pow(10, Power_SuntoEarthDistance));
		}

		float double planet_Z = 0;

		float double planet_RadiusMeters = EarthRadius * pow(10, Power_EarthRadius) + (Height * pow(10, Power_Height));

		float double user_Longidute = 0;
		if (earth_T_Seconds <= SecondsinDay / 2) {
			user_Longidute = Longitude + (earth_T_Seconds / SecondsinDay) * 360;
		}
		else {
			user_Longidute = Longitude - (360 - (earth_T_Seconds / SecondsinDay) * 360);
		}
		//Ignorando altitud
		float double user_Latitude = Latitude;
		//userLatitude = userLatitude - EarthInclination * cos(userLongidute * (PI / 180));			//Intentado calcular angulo de la tierra
		user_Latitude = 90 - user_Latitude;
		user_Latitude = user_Latitude + EarthInclination * sin((PI / 360) * (earth_Day - 80));
		printf("- Longitud Virtual:\t%Lf,\t Latitud Virtual:\t%Lf\n", Longitude, Latitude);
		printf("- Longitud Real:\t%Lf,\t Latitud Real:  \t%Lf\n", user_Longidute, user_Latitude);
		float double user_X = planet_RadiusMeters * sin(user_Latitude * (PI / 180)) * cos(user_Longidute * (PI / 180));
		float double user_Y = planet_RadiusMeters * sin(user_Latitude * (PI / 180)) * sin(user_Longidute * (PI / 180));
		float double user_Z = planet_RadiusMeters * cos(user_Latitude * (PI / 180));

		printf("- Coordenadas Tierra:\t\t\t X = %Lf\t, Y = %Lf\t, Z = %Lf\n", planet_X, planet_Y, planet_Z);
		printf("- Posicion Usuario relativa a la Tierra: X = %Lf\t, Y = %Lf\t, Z = %Lf\n", user_X, user_Y, user_Z);

		user_X = user_X + planet_X;
		user_Y = user_Y + planet_Y;
		user_Z = user_Z + planet_Z;

		printf("- Position Usuario real:\t\t X = %Lf\t, Y = %Lf\t, Z = %Lf\n", user_X, user_Y, user_Z);

		float double horizonNormalVector_X = user_X - planet_X;
		float double horizonNormalVector_Y = user_Y - planet_Y;
		float double horizonNormalVector_Z = user_Z - planet_Z;
		float double horizonEquationEquals = -(horizonNormalVector_X * -user_X + horizonNormalVector_Y * -user_Y + horizonNormalVector_Z * -user_Z);
		printf("- Ecuacion Plano del horizonte:\t %LfX + %LfY + %LfZ = %Lf\n", horizonNormalVector_X, horizonNormalVector_Y, horizonNormalVector_Z, horizonEquationEquals);


		float double angleBetweenHorizonandSun1 = abs(horizonNormalVector_X * user_X + horizonNormalVector_Y * user_Y + horizonNormalVector_Z * user_Z);
		float double angleBetweenHorizonandSun2 = pow(pow(horizonNormalVector_X, 2) + pow(horizonNormalVector_Y, 2) + pow(horizonNormalVector_Z, 2), 0.5) * pow(pow(user_X, 2) + pow(user_Y, 2) + pow(user_Z, 2), 0.5);
		float double angleBetweenHorizonandSun3 = asin(angleBetweenHorizonandSun1 / angleBetweenHorizonandSun2) * 180 / PI;
		printf("Angulo = %Lf\n", angleBetweenHorizonandSun3);
		i++;
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		printf("Fin del ciclo: %d\tTiempo de ejecucion: %d ms\n", i, duration.count());
		
		printf("\n");
		std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::milliseconds(1000-duration.count()));
}
*/