#pragma once
#include "Country.h"
#include "DynamicArray.h"
typedef struct
{
	DynamicArray* countries;
} World; //Country repository;

/// <summary>
/// Creates a Country Repo;
/// </summary>
World* createWorld();

/// <summary>
/// Destroys the dynamic array.
/// </summary>
/// <param name="w">The dynamic array to be destoyed.</param>
/// <returns>A pointer the the created dynamic array.</returns>
void destroyWorld(World* w);

/*
	Adds a country to the repository of countries.
	Input:	- w - pointer to the CountryRepo
			- c - country
	Output: 1 - if the country was sucessfully added
			0 - if the country could not be added, as another country with the same name already exists in the CountryRepo.
*/
int addCountryRepo(World* w, Country* c);

/*
	Deletes a country from the repository of countries.
	Input:	- w - pointer to the CountryRepo
			- c - country
	Output: 1 - if the country was sucessfully deleted
			0 - if the country could not be deleted, if the pos is wrong.
*/
int deleteCountryRepo(World* w, int pos);


/*
	Updates a country from the repository of countries.
	Input:	- w - pointer to the CountryRepo
			- c - country
	Output: 1 - if the country was sucessfully updated
			0 - if the country could not be deleted, if the pos is wrong.
*/
int update(World* w, char* name, char* newName, char* continent, int population);
int migrate(World* w, char* firstName, char* secondName, int population);



/// <summary>
/// Searches for the countries containing a given string.
/// </summary>
/// <param name="w">Pointer to the Repository.</param>
/// <param name = "symbols">A string, the searched string; "" - for all the countries.</param>
/// <returns>A pointer to a repository of countries, that have the given type.</returns>
Country* searchByName(World* w, char* name);

/*
	Returns the country on the given position in the country vector.
	Input:	v - the country repository;
			pos - integer, the position;
	Output: the country on the given potision, or an "empty" country.
*/
Country* getCountryOnPos(World* v, int pos);

/*
	Returns the position of the given country in the country vector.
	Input:	v - the country repository;
			pos - integer, the position;
	Output: the country on the given potision, or an "empty" country.
*/
int getCountryPos(World* w, char* name);

/// <summary>
/// Searches for the countries containing a given string.
/// </summary>
/// <param name="w">Pointer to the Repo.</param>
/// <param name = "symbols">A string, the searched string; "" - for all the countries.</param>
/// <returns>Countries that have the given type.</returns>
int filterByStringRepo(World* w, char symbols[]);

/// <summary>
/// Searches for the countries containing a given continent.
/// </summary>
/// <param name="w">Pointer to the Repo.</param>
/// <param name = "symbols">A string, the searched string; "" - for all the countries.</param>
/// <param name = "population"> The population to compare countries.</param>
/// <returns>Countries that have the given continent.</returns>
DynamicArray* filterByContinentRepo(World* w, char symbols[], int population);


/// Gets the repository length
int getRepoLength(World* w);