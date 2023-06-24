#pragma once
#include "AdminService.h"
#include "UserService.h"

class UI
{
private:
	AdminService& adminService;
	UserService& userService;

public:
	UI(AdminService& adminService, UserService& userService);

	void selectMode();
	void mainLoopAdmin();
	void mainLoopUser();

	void addCoat();
	void removeCoat();
	void updateCoat();
	void updateCoatSize(int size, int newSize);
	void updateCoatColour(int size, std::string newColour);
	void updateCoatPrice(int size, int newPrice);
	void updateCoatQuantity(int size, int newQuantity);
	void updateCoatPhotograph(int size, std::string newPhotograph);

	int addCoatToBasket(int pos);

	void printAllCoats();
	void printAllCoatsBasket();
	void printCoatUser();
	void printBasketFile(std::string fileType);
	void printCoat(int pos);

	int searchCoat(int size);

	void printAdminMenu();
	void printUserMenu();
};