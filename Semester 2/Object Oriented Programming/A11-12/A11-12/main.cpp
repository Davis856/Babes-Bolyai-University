#include <iostream>
#include <crtdbg.h>
#include "GUI.h"
#include <qapplication.h>
#include "Tests.h"

int main(int argc, char* argv[])
{
	Tests::testAll();

	QApplication a(argc, argv);

	std::string filename = "Repository.txt";

	std::string filename2 = "BasketTxt.txt";

	Repository repo{ filename };
	repo.InitializeRepo();
	Basket basket{ filename2 };
	AdminService adminService{ repo };
	UserService userService{ &basket };
	Validator validator{};
	GUI gui{ adminService, userService, validator, repo, basket };

	gui.show();

	return a.exec();
}
