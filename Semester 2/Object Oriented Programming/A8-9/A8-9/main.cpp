#include <iostream>
#include <crtdbg.h>
#include "UI.h"
#include "Tests.h"

int main()
{
	Tests::testAll();

	std::string filename = "Repository.txt";

	std::string filename2 = "BasketTxt.txt";

	Repository repo(filename);
	Basket basket(filename2);
	AdminService adminService(repo);
	UserService userService(&basket);
	UI ui(adminService, userService);

	ui.selectMode();

	return 0;
}
