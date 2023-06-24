#include <iostream>
#include <crtdbg.h>
#include "UI.h"
#include "Tests.h"

int main()
{
	Tests::testAll();

	Repository* repo = new Repository(10);
	Basket* basket = new Basket(10);
	AdminService* adminService = new AdminService(*repo);
	UserService* userService = new UserService(*basket);
	UI* ui = new UI(*adminService, *userService);

	ui->selectMode();

	delete ui;
	delete adminService;
	delete userService;
	delete repo;
	delete basket;

	int leak = _CrtDumpMemoryLeaks();

	std::cout << leak;

	return 0;
}
