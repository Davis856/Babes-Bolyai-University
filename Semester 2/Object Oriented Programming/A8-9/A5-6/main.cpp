#include <iostream>
#include <crtdbg.h>
#include "UI.h"
#include "Tests.h"

int main()
{
	//Tests::testAll();

	Repository repo;
	Basket basket;
	AdminService adminService(repo);
	UserService userService(basket);
	UI ui(adminService, userService);

	ui.selectMode();

	int leak = _CrtDumpMemoryLeaks();

	std::cout << leak;

	return 0;
}
