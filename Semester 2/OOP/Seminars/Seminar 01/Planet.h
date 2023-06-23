#pragma once

typedef struct
{
	char* name;
	char* type;
	double distanceFromEarth;
} Planet;

Planet* createPlanet(char* name, char* type, double distance);
void destroyPlanet(Planet* p);
char* getName(Planet p);
