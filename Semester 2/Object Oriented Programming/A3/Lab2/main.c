#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "Repository.h"
#include "UI.h"
#include "Tests.h"
#include <stdio.h>

int main()
{
	testAll();

	World* repo = createWorld();
	Service* serv = createService(repo);

	addCountryRepo(repo, createCountry("Romania", "Europe", 153103));
	addCountryRepo(repo, createCountry("Germany", "Europe", 41391531));
	addCountryRepo(repo, createCountry("USA", "America", 98528194));
	addCountryRepo(repo, createCountry("Japan", "Asia", 2500000));
	addCountryRepo(repo, createCountry("France", "Europe", 642992));
	addCountryRepo(repo, createCountry("Korea", "Asia", 850000));
	addCountryRepo(repo, createCountry("China", "Asia", 700000));
	addCountryRepo(repo, createCountry("South Africa", "Africa", 3189853));
	addCountryRepo(repo, createCountry("Australia", "Australia", 864653));
	addCountryRepo(repo, createCountry("Spain", "Europe", 43189058));

	UI* ui = createUI(serv);
	
	startUI(ui);

	destroyUI(ui);

	_CrtDumpMemoryLeaks();

	return 0;
}