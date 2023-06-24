#pragma once
#include "AdminService.h"
#include "UserService.h"

class UI
{
private:
	AdminService adminService;
	UserService userService;

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

	size_t addCoatToBasket(size_t pos);

	void printAllCoats();
	void printAllCoatsBasket();
	void printCoatUser();
	void printCoat(size_t pos);

	size_t searchCoat(size_t size);

	void printAdminMenu();
	void printUserMenu();
};