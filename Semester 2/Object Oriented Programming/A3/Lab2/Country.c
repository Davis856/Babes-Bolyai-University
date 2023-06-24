#include "Country.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Country* createCountry(char* name, char* continent, int population)
{
	Country* c = malloc(sizeof(Country));
	if (c == NULL)
		return NULL;
	c->name = malloc(sizeof(char) * (strlen(name) + 1));
	if (c->name != NULL)
		strcpy(c->name, name);
	c->continent = malloc(sizeof(char) * (strlen(continent) + 1));
	if (c->continent != NULL)
		strcpy(c->continent, continent);

	c->population = population;

	return c;
}

void destroyCountry(Country* c)
{
	if (c == NULL)
		return;

	// free the memory which was allocated for the component fields
	free(c->name);
	free(c->continent);

	// free the memory which was allocated for country structure
	free(c);
}

char* getName(Country* c)
{
	if (c == NULL)
		return NULL;
	return c->name;
}

char* getContinent(Country* c)
{
	if (c == NULL)
		return NULL;
	return c->continent;
}

int getPopulation(Country* c)
{
	if (c == NULL)
		return -1;
	return c->population;
}

char* setName(Country* c, char value[])
{
	if (c == NULL)
		return NULL;
	strcpy(c->name, value);
}

char* setContinent(Country* c, char value[])
{
	if (c == NULL)
		return NULL;
	strcpy(c->continent, value);
}

int setPopulation(Country* c, int value)
{
	if (c == NULL)
		return -1;
	c->population = value;
}
void toString(Country* c, char str[])
{
	if (c == NULL)
		return;
	sprintf(str, "Country %s is in %s continent and it has a population of %d. \n", c->name, c->continent, c->population);
}

Country* copyCountry(Country* c)
{
	if (c == NULL)
		return NULL;
	
	return createCountry(c->name, c->continent, c->population);
}