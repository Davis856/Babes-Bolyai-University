#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "Service.h"
#include <string.h>
#include "Operation.h"

Service* createService(World* w)
{
	Service* s = (Service*)malloc(sizeof(Service));
	if (s == NULL)
		return NULL;

	s->repo = w;
	s->undoStack = createDynamicArray(10, &destroyOperation);
	s->redoStack = createDynamicArray(10, &destroyOperation);

	return s;
}

void destroyService(Service* s)
{
	if (s == NULL)
		return;

	// first destroy the repository inside
	destroyWorld(s->repo);
	destroy(s->undoStack);
	// then free the memory
	free(s);
}

World* getRepo(Service* s)
{
	return s->repo;
}

int addCountry(Service* s, char* name, char* continent, int population)
{
	if (s == NULL)
		return -1;

	for (int i = 0; i < 6; i++)
		if (strcmp(continent, "Europe") != 0 && strcmp(continent, "America") != 0 && strcmp(continent, "Africa") != 0 && strcmp(continent, "Australia") != 0 && strcmp(continent, "Asia") != 0)
			return -1;

	if (population < 0)
		return -1;

	Country* c = createCountry(name, continent, population);

	int res = addCountryRepo(s->repo, c);
	// if the country was not added - destroy it (as it will be not destroyed by the repository)
	if (res == 0)
	{
		Operation* op = createOperation(ADD, c);
		if (op == NULL)
			return -1;
		add(s->undoStack, op);
	}

	return res;
}

int deleteCountry(Service* s, int pos)
{
	if (s == NULL)
		return -1;

	if (pos <= getLength(s->repo->countries))
	{
		Country* c = getCountryOnPos(s->repo, pos);

		Operation* op = createOperation(DELETE, c);
		if (op == NULL)
			return -1;
		add(s->undoStack, op);
	}
	return deleteCountryRepo(s->repo, pos);
}

int updateCountry(Service* s, char* name, char* newName, char* continent, int population)
{
	
	if (s == NULL)
		return -1;

	int res = update(s->repo, name, newName, continent, population);
	if (res == 0)
	{
		Country* c = createCountry(name, continent, population);

		Operation* op = createOperation(UPDATE, c);
		if (op == NULL)
			return -1;
		add(s->undoStack, op);
	}

	return res;
}

int migrateCountry(Service* s, char* firstName, char* secondName, int population)
{
	if (s == NULL)
		return -1;

	int res = migrate(s->repo, firstName, secondName, population);

	return res;
	
}


int filterByString(Service* s, char symbols[])
{
	if (s == NULL)
		return -1;

	int res = filterByStringRepo(s->repo, symbols);

	return res;

}

DynamicArray* filterByContinent(Service* s, char symbols[], int population)
{
	if (s == NULL)
		return NULL;

	DynamicArray* res = filterByContinentRepo(s->repo, symbols, population);

	return res;

}

int undo(Service* s)
{
	if (s == NULL)
		return -1; // error

	int stackSize = getLength(s->undoStack);
	if (stackSize == 0)
		return 1; // no more undos
	Operation* op = get(s->undoStack, stackSize - 1);
	if (op == NULL)
		return -1;
	Country* c = getOpObject(op);
	if (c == NULL)
		return -1;

	if (getOpType(op) == ADD)
		deleteCountryRepo(s->repo, getCountryPos(s->repo, getName(c)));
	else if (getOpType(op) == DELETE)
		addCountryRepo(s->repo, copyCountry(c)); // must have a copy, because c
										   // will be destroyed when deleting
										   // the operation from the stack

	Operation* op2 = op;
	// remove the operation from "the stack"
	// should be added to the redo stack
	delete(s->undoStack, stackSize - 1);
	return 0;
}

int redo(Service* s)
{
	if (s == NULL)
		return -1; // error

	int stackSize = getLength(s->undoStack);
	if (stackSize == 0)
		return 1; // no more redos
	Operation* op = get(s->undoStack, stackSize - 1);
	if (op == NULL)
		return -1;
	Country* c = getOpObject(op);
	if (c == NULL)
		return -1;

	if (getOpType(op) == ADD)
		addCountryRepo(s->repo, copyCountry(c));
	else if (getOpType(op) == DELETE)
		deleteCountryRepo(s->repo, getCountryPos(s->repo, getName(c)));

	Operation* op2 = op;

	add(s->undoStack, op2);
	return 0;
}