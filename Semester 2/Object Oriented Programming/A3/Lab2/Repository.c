#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "Repository.h"
#include <string.h>
#include <stdio.h>


World* createWorld()
{
	World* w = (World*)malloc(sizeof(World));
	// make sure the space was allocated
	if (w == NULL)
		return NULL;
	w->countries = createDynamicArray(CAPACITY, &destroyCountry);

	return w;
}

void destroyWorld(World* w)
{
	if (w == NULL)
		return;
		
	destroy(w->countries);
	free(w);
}

Country* searchByName(World* w, char* name)
{
	if (w == NULL || name == NULL)
		return NULL;

	for (int i = 0; i < getLength(w->countries); i++)
	{
		Country* c = get(w->countries, i);
		if (strcmp(getName(c), name) == 0)
			return c;
	}

	return NULL;
}

int addCountryRepo(World* w, Country* c)
{
	if (w == NULL || c == NULL)
		return -1;

	add(w->countries, c);

	return 0;
}

int deleteCountryRepo(World* w, int pos)
{
	if (w == NULL || &pos == NULL)
		return -1;
	Country* c = getCountryOnPos(w, pos);
	for (int i = 0; i < getLength(w->countries); i++)
	{
		if (get(w->countries, i) == c)
		{
			delete(w->countries, i);
			return 0;
		}
	}
	
	return -1;
}

int update(World* w, char* name, char* newName, char* continent, int population)
{

	if (strcmp(newName, "default") != 0)
	{
		int allow = 0;
		for (int i = 0; i < getRepoLength(w); i++)
		{
			if (strcmp(name, getName(get(w->countries, i))) == 0)
			{
				allow = 1;
				break;
			}
		}	


		if (allow)
		{
			Country* c = searchByName(w, name);
			setName(c, newName);
			return 1;
		}
		else
			return 0;
		
	}
	if (strcmp(continent, "default") != 0)
	{
		int allow1 = 0, allow2 = 0;
		for (int i = 0; i <= getRepoLength(w); i++)
			if (strcmp(name, getName(get(w->countries, i))) == 0)
			{
				allow1 = 1;
				break;
			}

		for (int i = 0; i < 6; i++)
			if (strcmp(continent, "Europe") == 0 || strcmp(continent, "America") == 0 || strcmp(continent, "Africa") == 0 || strcmp(continent, "Australia") == 0 || strcmp(continent, "Asia") == 0)
			{
				allow2 = 1;
				break;
			}
		
		if (allow1 && allow2)
		{
			Country* c = searchByName(w, name);
			setContinent(c, continent);
			return 1;
		}
		else
			return 0;
	}
	if (population != 0)
	{
		int allow1 = 0;
		for (int i = 0; i <= getRepoLength(w); i++)
			if (strcmp(name, getName(get(w->countries, i))) == 0)
			{
				allow1 = 1;
				break;
			}

		if (allow1)
		{
			Country* c = searchByName(w, name);
			setPopulation(c, population);
			return 1;
		}
		else
			return 0;
	}
	return 0;
}


int migrate(World* w, char* firstName, char* secondName, int population)
{
	int allow1 = 0;
	for (int i = 0; i <= getRepoLength(w); i++)
		if (strcmp(firstName, getName(get(w->countries, i))) == 0)
		{
			allow1 = 1;
			break;
		}

	int allow2 = 0;
	for (int i = 0; i <= getRepoLength(w); i++)
		if (strcmp(secondName, getName(get(w->countries, i))) == 0)
		{
			allow2 = 1;
			break;
		}

	if (allow1 && allow2)
	{
		Country* c = searchByName(w, firstName);
		Country* d = searchByName(w, secondName);

		if (getPopulation(c) - population < 0)
			return 0;


		setPopulation(c, getPopulation(c) - population);
		setPopulation(d, getPopulation(d) + population);

		return 1;
	}
	else
		return 0;
	
}


Country* getCountryOnPos(World* w, int pos)
{
	if (w == NULL)
		return NULL;
	if (pos < 0 || pos >= getRepoLength(w))
		return NULL;
	return get(w->countries, pos);
}

int getCountryPos(World* w, char* name)
{
	if (w == NULL || name == NULL)
		return -1;

	Country* c = searchByName(w, name);
	for (int i = 0; i < getRepoLength(w); i++)
	{
		if (strcmp(getName(w->countries->elems[i]), getName(c)) == 0)
		{
			return i;
		}
	}
	return 0;
}

int getRepoLength(World* w)
{
	if (w == NULL)
		return -1;
	
	return getLength(w->countries);
}

int filterByStringRepo(World* w, char symbols[])
{
	if (strcmp(symbols, "all") == 0)
	{
		for (int i = 0; i < getRepoLength(w); i++)
		{
			Country* country = getCountryOnPos(w, i);
			char countryString[200];
			toString(country, countryString);
			printf("%s\n", countryString);
		}
	}
	for (int i = 0; i < getRepoLength(w); i++)
	{
		char* ret;
		ret = strstr(getName(get(w->countries, i)), symbols);
		if (ret != NULL)
		{
			Country* country = getCountryOnPos(w, i);
			char countryString[200];
			toString(country, countryString);
			printf("%s\n", countryString);
		}
	}

	return 1;
}

DynamicArray* filterByContinentRepo(World* w, char symbols[], int population)
{
	DynamicArray* repo = createDynamicArray(CAPACITY, &destroyCountry);
	if (strcmp(symbols, "all") == 0)
	{
		for (int i = 0; i < getRepoLength(w); i++)
		{
			if (getPopulation(get(w->countries, i)) >= population)
			{
				Country* c = getCountryOnPos(w, i);
				add(repo, c);
			}
		}
		for (int i = 0; i < getLength(repo) - 1; i++)
		{
			Country* aux;
			for (int j = i + 1; j < getLength(repo); j++)
			{
				if (getPopulation(repo->elems[i]) > getPopulation(repo->elems[j]))
				{
					aux = repo->elems[i];
					repo->elems[i] = repo->elems[j];
					repo->elems[j] = aux;
				}
			}
		}
		return repo;
	}
	else
	{
		for (int i = 0; i < getRepoLength(w); i++)
		{
			int ret = 0;
			ret = strcmp(getContinent(get(w->countries, i)), symbols);
			if (ret == 0 && getPopulation(get(w->countries, i)) >= population)
			{
				Country* c = getCountryOnPos(w, i);
				add(repo, c);
			}
		}
		for (int i = 0; i < getLength(repo) - 1; i++)
		{
			Country* aux;
			for (int j = i + 1; j < getLength(repo); j++)
			{
				if (getPopulation(repo->elems[i]) > getPopulation(repo->elems[j]))
				{
					aux = repo->elems[i];
					repo->elems[i] = repo->elems[j];
					repo->elems[j] = aux;
				}
			}
		}
		return repo;
	}
	return 0;
}