#pragma once
#include "Repository.h"
typedef struct
{
	World* repo;
	DynamicArray* undoStack;
	DynamicArray* redoStack;
}Service;

Service* createService(World* w);
void destroyService(Service* s);

/// <summary>
/// Adds a country to the repository of countries.
/// </summary>
/// <param name="s">Pointer to the Service.</param>
/// <param name = "name">A string, the name of the country.</param>
/// <param name = "continent">A string, the country's continent.</param>
/// <param name = "population">Int, the country's population.</param>
/// <returns>1 - if the country was sucessfully added; 0 - if the country could not be added, as another country with the same name already exists.</returns>
int addCountry(Service* s, char* name, char* continent, int population);

/// <summary>
/// Updates a country from the repository of countries.
/// </summary>
/// <param name="s">Pointer to the Service.</param>
/// <param name = "name">A string, the name of the country.</param>
/// <param name = "newName">A string, the new name of the country if necessary.</param>
/// <param name = "continent">A string, the country's continent.</param>
/// <param name = "population">Int, the country's population.</param>
/// <returns>1 - if the country was sucessfully modified; 0 - if the country could not be modified.</returns>
int updateCountry(Service* s, char* name, char* newName, char* continent, int population);

/// <summary>
/// Updates a country from the repository of countries.
/// </summary>
/// <param name="s">Pointer to the Service.</param>
/// <param name = "firstName">A string, the name of the country.</param>
/// <param name = "secondName">A string, the new name of the country if necessary.</param>
/// <param name = "population">Int, the country's population.</param>
/// <returns>1 - if the country was sucessfully modified; 0 - if the country could not be modified.</returns>
int migrateCountry(Service* s, char* firstName, char* secondName, int population);

/// <summary>
/// Deletes a country from the repository of countries.
/// </summary>
/// <param name="s">Pointer to the Service.</param>
/// <param name = "name">A country, the one to be deleted.</param>
/// <returns>1 - if the country was sucessfully deleted; 0 - if the country could not be deleted.</returns>
int deleteCountry(Service* s, int pos);

/// <summary>
/// Gets the repo of the service
/// </summary>
/// <param name="s">Pointer to the Service.</param>
/// <returns>Repo of countries.</returns>
World* getRepo(Service* s);

/// <summary>
/// Searches for the countries containing a given string.
/// </summary>
/// <param name="s">Pointer to the Service.</param>
/// <param name = "symbols">A string, the searched string; "" - for all the countries.</param>
/// <returns>A pointer to a repository of countries, that have the given type.</returns>
int filterByString(Service* s, char symbols[]);

/// <summary>
/// Searches for the countries containing a given string.
/// </summary>
/// <param name="s">Pointer to the Service.</param>
/// <param name = "symbols">A string, the searched string; "" - for all the countries.</param>
/// <param name = "population"> The population to compare countries.</param>
/// <param name = "sortType"> For bonus, sort ascending or descending. </param>
/// <returns>A pointer to a repository of countries, that have the given continent.</returns>
DynamicArray* filterByContinent(Service* s, char symbols[], int population);

/*
* Return 0 - succes; -1 - error; 1 - no more undos
*/
int undo(Service* s);

/*
* Return 0 - succes; -1 - error; 1 - no more redos
*/
int redo(Service* s);