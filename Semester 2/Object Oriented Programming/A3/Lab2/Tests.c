#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "UI.h"

void testAdd()
{
	World* w = createWorld();

	Country* c1 = createCountry("Romania", "Europe", 1000);
	addCountryRepo(w, c1);
	assert(getRepoLength(w) == 1);
	assert(strcmp(getName(getCountryOnPos(w, 0)), "Romania") == 0);
	
	Country* c2 = createCountry("Germany", "Europe", 2000);
	assert(addCountryRepo(w, c2) == 0);
	assert(getRepoLength(w) == 2);

	destroyWorld(w);
}

void testDestroy()
{
	World* w = createWorld();
	Country* c1 = createCountry("Romania", "Europe", 1000);
	addCountryRepo(w, c1);
	Country* c2 = createCountry("Germany", "Europe", 100000);
	addCountryRepo(w, c2);
	assert(getRepoLength(w) == 2);
	deleteCountryRepo(w, 1);
	assert(getRepoLength(w) == 1);

	assert(deleteCountryRepo(w, 2) == -1);
	
	destroyWorld(w);
}

void testUpdate()
{
	World* w = createWorld();

	Country* c1 = createCountry("Romania", "Europe", 4000);

	addCountryRepo(w, c1);
	//test first update, name
	update(w, "Romania", "Germany", "default", 0);
	assert(strcmp(getName(get(w->countries, 0)), "Germany") == 0);
	//test continent update
	update(w, "Germany", "default", "Asia", 0);
	assert(strcmp(getContinent(w->countries->elems[0]), "Asia") == 0);
	//test population update
	update(w, "Germany", "default", "default", 2000);
	assert(getPopulation(w->countries->elems[0]) == 2000);
	//test migration
	Country* c2 = createCountry("Spain", "Europe", 1000);
	addCountryRepo(w, c2);
	migrate(w, "Germany", "Spain", 1000);
	assert(getPopulation(get(w->countries, 0)) == 1000);
	assert(getPopulation(get(w->countries, 1)) == 2000);
	
	destroyWorld(w);
}

void testAll()
{
	testAdd();
	testDestroy();
	testUpdate();
}
