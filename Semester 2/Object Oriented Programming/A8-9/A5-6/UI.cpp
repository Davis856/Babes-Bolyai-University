#include "UI.h"
#include <iostream>
#include <Windows.h>
#include <shellapi.h>

using namespace std;

UI::UI(AdminService& adminService, UserService& userService) : adminService{ adminService }, userService{ userService }
{
	adminService.InitializeRepo();
}

void UI::selectMode()
{
	bool done = false;

	while (!done)
	{
		int mode = 0;
		cout << "Select application mode:\n";
		cout << "1.Admin mode\n";
		cout << "2.User mode\n";
		cin >> mode;

		
		if (mode != 1 && mode != 2)
		{
			cout << "Invalid mode!\n";
			return;
		}
		switch (mode)
		{
		case 1:
		{
			mainLoopAdmin();
			done = true;
			break;
		}
		case 2:
		{
			mainLoopUser();
			done = true;
			break;
		}
		default:
		{
			cout << "Invalid mode!\n";
			done = true;
			break;
		}
		}
	}
}

void UI::printAdminMenu()
{
	cout << "1. Add a new coat\n";
	cout << "2. Remove a coat by size\n";
	cout << "3. Update a coat\n";
	cout << "4. Print all coats\n";
	cout << "0. Exit\n";
}

void UI::printUserMenu()
{
	cout << "1. Search for coats.\n";
	cout << "2. See basket\n";
	cout << "0. Exit\n";
}

void UI::mainLoopAdmin()
{
	string command;
	bool done = false;
	
	while (!done)
	{
		printAdminMenu();
		std::cout << "\nPlease input your command:\n";
		std::cin >> command;
		if (command.size() != 1)
			std::cout << "Invalid command!\n";
		else {
			try {
				switch (command[0])
				{
				case '1':
				{
					addCoat();
					break;
				}
				case '2':
				{
					removeCoat();
					break;
				}
				case '3':
				{
					updateCoat();
					break;
				}
				case '4':
				{
					printAllCoats();
					break;
				}
				case '0':
				{
					done = true;
					break;
				}
				default:
				{
					std::cout << "Invalid command!\n";
					break;
				}
				}

			}
			catch (std::exception& e)
			{
				std::cout << e.what() << "\n";
			}
		}
	}
}

void UI::mainLoopUser()
{
	string command;
	while (true)
	{
		printUserMenu();
		std::cout << "Please input your command: \n";
		std::cin >> command;
		if (command.size() != 1)
			std::cout<<"Invalid command\n";
		else
			switch (command[0])
			{
			case '1':
			{
				printCoatUser();
				break;
			}
			case '2':
			{
				printAllCoats();
				break;
			}
			case '0':
			{
				return;
			}
			default:
			{
				std::cout << "Invalid command!\n";
				break;
			}
			}
	}
}

void UI::addCoat()
{
	string colour, photograph;
	int size, quantity, price;
	cout << "Enter size, colour, price, quantity, photograph link:\n";
	cin >> size;
	cin >> colour;
	cin >> price;
	cin >> quantity;
	cin >> photograph;

	this->adminService.addCoat(size, colour, price, quantity, photograph);
}

size_t UI::addCoatToBasket(size_t pos)
{
	Coat newCoat = adminService.getRepo().getArray()[pos];
	this->adminService.updateCoatQuantity(newCoat.getSize(), newCoat.getQuantity() - 1);
	size_t elem = adminService.getRepo().FindElemBySize(pos);
	bool added = false;
	for (int i = 0; i < userService.getRepo().getSize(); i++)
	{
		if (newCoat.getSize() == userService.getRepo().getArray()[i].getSize()) // TODO - fix this
		{
			this->userService.updateCoatQuantity(i, userService.getRepo().getArray()[i].getQuantity() + 1);
			added = true;
			break;
		}
	}
	if(added == false)
		this->userService.addCoatToBasket(newCoat.getSize(), newCoat.getColour(), newCoat.getPrice(), 1, newCoat.getPhotograph());
	return newCoat.getPrice();
}

void UI::removeCoat()
{
	size_t size;
	cout << "Enter the size of the coat that you want to remove: \n";
	cin >> size;
	this->adminService.removeCoat(size);
}

void UI::updateCoat()
{
	int size;
	cout << "Enter the size of the coat that you want to update:\n";
	cin >> size;
	cout << "Enter the attribute that you want to modify:\n";
	cout << "S - size, C - colour, P - price, Q - quantity, F - photograph\n";

	string attr;
	cin >> attr;

	if (attr.size() != 1)
	{
		cout << "Invalid attribute.\n";
		return;
	}
	switch (attr[0])
	{
	case 's':
	case 'S':
	{
		int newSize;
		cout << "Enter the new size of the coat:\n";
		cin >> newSize;
		updateCoatSize(size, newSize);
		break;
	}
	case 'c':
	case 'C':
	{
		string newColour;
		cout << "Enter the new colour of the coat:\n";
		cin >> newColour;
		updateCoatColour(size, newColour);
		break;
	}
	case 'p':
	case 'P':
	{
		int newPrice;
		cout << "Enter the new price of the coat:\n";
		cin >> newPrice;
		updateCoatPrice(size, newPrice);
		break;
	}
	case 'q':
	case 'Q':
	{
		int newQuantity;
		cout << "Enter the new quantity of the coat:\n";
		cin >> newQuantity;
		updateCoatQuantity(size, newQuantity);
		break;
	}
	case 'f':
	case 'F':
	{
		string newPhotograph;
		cout << "Enter the new photograph link of the coat:\n";
		cin >> newPhotograph;
		updateCoatPhotograph(size, newPhotograph);
		break;
	}
	default:
	{
		cout << "Invalid attribute.\n";
		break;
	}
	}
}

void UI::updateCoatSize(int size, int newSize)
{
	this->adminService.updateCoatSize(size, newSize);
}

void UI::updateCoatColour(int size, string newColour)
{
	this->adminService.updateCoatColour(size, newColour);
}

void UI::updateCoatPrice(int size, int newPrice)
{
	this->adminService.updateCoatPrice(size, newPrice);
}

void UI::updateCoatQuantity(int size, int newQuantity)
{
	this->adminService.updateCoatQuantity(size, newQuantity);
}

void UI::updateCoatPhotograph(int size, string newPhotograph)
{
	this->adminService.updateCoatPhotograph(size, newPhotograph);
}

void UI::printAllCoats()
{
	cout << adminService.getRepo();
}

void UI::printAllCoatsBasket()
{
	cout << userService.getRepo();
}

size_t UI::searchCoat(size_t size)
{
	Repository repo = adminService.getRepo();
	DynamicVector<Coat> coats = repo.getArray();
	size_t elem = repo.FindElemBySize(size);
	if (elem == -1)
		cout << "Error, the coat does not exist!";
	else
		cout << coats[elem];
	return elem;
}

void UI::printCoat(size_t pos)
{
	cout << adminService.getRepo().getArray()[pos];
}

void UI::printCoatUser()
{
	size_t size = 0;
	size_t price = 0;
	while (true)
	{
		cout << "Type the size of the coat that you want to see.\n";
		cin >> size;
		size_t elemSize = searchCoat(size);
		int option = 0;
		while (true)
		{
			cout << "Select an option for the coat:\n";
			cout << "1. Add coat to basket.\n";
			cout << "2. Go to the next coat.\n";
			cout << "3. Print current basket items.\n";
			cout << "0. Exit.\n";
			system(string("start " + this->adminService.getRepo().getArray()[elemSize].getPhotograph()).c_str());
			cin >> option;
			if (option == 1)
			{
				price += addCoatToBasket(elemSize);
				printAllCoatsBasket();
				cout << "Total price: " << price << " $" << endl;

			}
			else if (option == 2)
			{
				if (elemSize + 1 < adminService.getRepo().getSize())
					elemSize++;
				else
					elemSize = 0;
				printCoat(elemSize);
				system(string("start " + this->adminService.getRepo().getArray()[elemSize].getPhotograph()).c_str());
			}
			else if (option == 3)
			{
				printAllCoatsBasket();
				cout << "Total price: " << price << " $" << endl;
			}
			else if (option == 0)
				return;
		}
	}
}