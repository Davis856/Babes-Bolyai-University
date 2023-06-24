#pragma once

typedef struct 
{
	char* name;
	char* continent;
	int population;
} Country;


Country* createCountry(char* name, char* continent, int population);
void destroyCountry(Country* c); // the memory is freed

Country* copyCountry(Country* c);

char* getName(Country* c);
char* getContinent(Country* c);
int getPopulation(Country* c);

char* setName(Country* c, char value[]);
char* setContinent(Country* c, char value[]);
int setPopulation(Country* c, int value);

void toString(Country* c, char str[]);