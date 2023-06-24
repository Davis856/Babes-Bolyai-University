#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "UI.h"
#include <stdio.h>

UI* createUI(Service* s)
{
	UI* ui = (UI*)malloc(sizeof(UI));
	if (ui == NULL)
		return NULL;
	ui->serv = s;

	return ui;
}

void destroyUI(UI* ui)
{
	if (ui == NULL)
		return;

	//first we destroy the service
	destroyService(ui->serv);

	//free the UI memory
	free(ui);
}

/*
	Prints the available menu for the problem
	Input: -
	Output: the menu is printed at the console
*/
void printMenu()
{
	printf("\n**********************************************************\n");
	printf("1 - add a country.\n");
	printf("2 - list all countries.\n");
	printf("3 - delete a country.\n");
	printf("4 - display all countries whose name contains a given string.\n");
	printf("5 - update country.\n");
	printf("6 - display all countries from a given continent.\n");
	printf("7 - undo last action.\n");
	printf("8 - redo last action.\n");
	printf("0 - to exit.\n");
	printf("**********************************************************\n");
}

/*
	Verifies if the given command is valid (is either 1, 2 or 0)
	Input: command - integer
	Output: 1 - if the command is valid
	0 - otherwise
*/
int validCommand(int command)
{
	if (command >= 0 && command <= 8)
		return 1;
	return 0;
}

/*
	Reads an integer number from the keyboard. Asks for number while read errors encoutered.
	Input: the message to be displayed when asking the user for input.
	Returns the number.
*/
int readIntegerNumber(const char* message)
{
	char s[16] = { 0 };
	int res = 0;
	int flag = 0;
	int r = 0;

	while (flag == 0)
	{
		printf(message);
		int scanf_result = scanf("%15s", s);

		r = sscanf(s, "%d", &res);	// reads data from s and stores them as integer, if possible; returns 1 if successful
		flag = (r == 1);
		if (flag == 0)
			printf("Error reading number!\n");
	}
	return res;
}

int addCountryUI(UI* ui)
{
	// read the countries's data
	char name[50], continent[50];
	int population = 0;

	printf("Please input the name: ");
	int scanf_result = scanf("%49s", name);
	printf("Please input the continent (one of Europe, America, Africa, Australia, Asia): ");
	scanf_result = scanf("%49s", continent);
	printf("Please input the country's population: ");
	scanf_result = scanf("%d", &population);

	return addCountry(ui->serv, name, continent, population);	
}

int updateCountryUI(UI* ui)
{
	int option = 0;
	printf("What do you want to update? \n");
	printf("1. Update name\n");
	printf("2. Update continent\n");
	printf("3. Update population\n");
	printf("4. Migrate population\n");
	int scanf_result = scanf("%d", &option);
	switch (option)
	{
		case 1:
		{
			char oldName[50], newName[50];
			printf("Please input the name of the country that you want to change: ");
			int scanf_result = scanf("%49s", oldName);
			printf("Please input the new name of the country: ");
			scanf_result = scanf("%49s", newName);

			return updateCountry(ui->serv, oldName, newName, "default", 0);
		}
		case 2:
		{
			char name[50], continent[50];
			printf("Please input the name of the country that you want to change: ");
			int scanf_result = scanf("%49s", name);
			printf("Please input the new continent of the country: ");
			scanf_result = scanf("%49s", continent);

			return updateCountry(ui->serv, name, "default", continent, 0);
		}
		case 3:
		{
			char name[50];
			int population = 0;
			printf("Please input the name of the country that you want to change: ");
			int scanf_result = scanf("%49s", name);
			printf("Please input the new population of the country: ");
			scanf_result = scanf("%d", &population);

			return updateCountry(ui->serv, name, "default", "default", population);
		}
		case 4:
		{
			char firstName[50], secondName[50];
			int population = 0;
			printf("Please input the name of the country that the people migrate from: ");
			int scanf_result = scanf("%49s", firstName);
			printf("Please input the name of the country that the people migrate to: ");
			scanf_result = scanf("%49s", secondName);
			printf("Please input the population number: ");
			scanf_result = scanf("%d", &population);

			return migrateCountry(ui->serv, firstName, secondName, population);
		}
	}
	return 0;
}


int destroyCountryUI(UI* ui)
{
	int pos = 0;
	printf("Please enter the country position that you want to delete: ");
	int scanf_result = scanf("%d", &pos);
	pos--;

	return deleteCountry(ui->serv, pos);
}

void listAllCountries(UI* ui)
{
	if (ui == NULL)
		return;
	World* repo = getRepo(ui->serv);
	if (repo == NULL)
		return;
	for (int i = 0; i < getRepoLength(repo); i++)
	{
		Country* country = getCountryOnPos(repo, i);
		char countryString[200];
		toString(country, countryString);
		printf("%s\n", countryString);
	}
}

int listCountriesByString(UI* ui)
{
	char symbols[50];
	printf("Please input the string: input 'all' for all countries: ");
	int scanf_result = scanf("%49s", symbols);

	int res = filterByString(ui->serv, symbols);

	return res;
}

void listCountriesByContinent(UI* ui)
{
	char symbols[50];
	int population = 0;
	printf("Please input the continent name: input 'all' for all countries: \n");
	printf("If the continent does not have any countries, all will be displayed. \n");
	int scanf_result = scanf("%49s", symbols);
	printf("Please input the population limit: \n");
	scanf_result = scanf("%d", &population);

	DynamicArray* res = filterByContinent(ui->serv, symbols, population);

	char stringCountry[200];

	for (int i = 0; i < getLength(res); i++)
	{
		toString(res->elems[i], stringCountry);
		printf("%s", stringCountry);
	}
}

int undoUI(UI* ui)
{
	return undo(ui->serv);
}

int redoUI(UI* ui)
{
	return redo(ui->serv);
}

void startUI(UI* ui)
{
	while (1)
	{
		printMenu();
		int command = readIntegerNumber("Input command: ");
		while (validCommand(command) == 0)
		{
			printf("Please input a valid command!\n");
			command = readIntegerNumber("Input command: ");
		}
		if (command == 0)
			break;
		switch (command)
		{
			case 1:
			{
				int res = addCountryUI(ui);
				if (res == 0)
					printf("Country successfully added.\n");
				else
					printf("Error! Country could not be added, as there is another country with the same name or the continent is invalid, or population is a negative number! \n");
				break;
			}
			case 2:
			{
				listAllCountries(ui);
				break;
			}
			case 3:
			{
				int res = destroyCountryUI(ui);
				if (res == 0)
					printf("Country deleted!\n");
				else
					printf("Error! Country does not exist!\n");
				break;
			}
			case 4:
			{
				listCountriesByString(ui);
				break;
			}
			case 5:
			{
				int res = updateCountryUI(ui);
				if (res == 1)
					printf("Country successfully updated!\n");
				else
					printf("Country could not be updated! Check if the input is correct.");
				break;
			}
			case 6:
			{
				listCountriesByContinent(ui);
				break;
			}
			case 7:
			{
				int res = undoUI(ui);
				if (res == 0)
					printf("Undo successful");
				else
					printf("Cannot undo!");
				break;
			}
			case 8:
			{
				int res = redoUI(ui);
				if (res == 0)
					printf("Redo successful");
				else
					printf("Cannot redo!");
				break;
			}
		}
	}
}