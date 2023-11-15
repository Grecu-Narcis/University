#include "Planet.h"
#include <stdlib.h>

Planet* createPlanet(char* name, char* type, double distance)
{
	Planet* p = malloc(sizeof(Planet));
	p->name = malloc((strlen(name) + 1) * sizeof(char));

	if (p.name == NULL)
		return p;

	strcpy(p->name, name);

	p->type = malloc((strlen(type) + 1) * sizeof(char));

	if (p->type == NULL)
	{
		free(p->name);
		return p;
	}

	strcpy(p->type, type);

	p->distanceFromEarth = distance;

	return p;
}

void destroyPlanet(Planet* p)
{
	free(p->name);
	free(p->type);

	free(p);
}

char* getName(Planet p)
{
	
}
