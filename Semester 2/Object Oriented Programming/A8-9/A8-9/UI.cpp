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
	
	while (true)
	{
		printAdminMenu();
		std::cout << "\nPlease input your command:\n";
		std::cin >> command;
		if (command.size() != 1)
			std::cout << "Invalid command!\n";
		else {
			try 
			{
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
					return;
				}
				default:
				{
					std::cout << "Invalid command!\n";
					break;
				}
				}

			}
			catch (ServiceException& ex)
			{
				std::cout << ex.what() << "\n";
			}
		}
	}
}

void UI::mainLoopUser()
{
	std::cout << "Please enter the type of the file in which you want to save the shopping basket(csv or html):" << std::endl;
	std::string fileType;
	while (true)
	{
		try
		{
			cin >> fileType;
			this->userService.repositoryType(fileType);
			break;
		}
		catch (UserException& ex)
		{
			std::cout << ex.what() << std::endl;
		}
	}
	string command;
	while (true)
	{
		printUserMenu();
		std::cout << "Please input your command: \n";
		std::cin >> command;
		if (command.size() != 1)
			std::cout << "Invalid command\n";
		else
		{
			try
			{
				switch (command[0])
				{
				case '1':
				{
					printCoatUser();
					break;
				}
				case '2':
				{
					printAllCoatsBasket();
					break;
				}
				case '3':
				{
					string fileType;
					cout << "Enter the file type(csv or html):" << endl;
					cin >> fileType;
					printBasketFile(fileType);
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
			catch (UserException& ex)
			{
				std::cout << ex.what() << std::endl;
			}
		}	
		
	}
}

void UI::addCoat()
{
	string colour, photograph, size1, quantity1, price1;
	int size, quantity, price, ok=0;
	cout << "Enter size, colour, price, quantity, photograph link:\n";
	cin >> size1;
	cin >> colour;
	cin >> price1;
	cin >> quantity1;
	cin >> photograph;
	for (char const& c : size1)
	{
		if (!std::isdigit(c))
		{
			ok = 0;
			break;
		}
	}
	for (char const& c : quantity1)
	{
		if (!std::isdigit(c))
		{
			ok = 0;
			break;
		}
	}
	for (char const& c : price1)
	{
		if (!std::isdigit(c))
		{
			ok = 0;
			break;
		}
	}
	if (!ok)
		cout << "Wrong parameter type."<<endl;
	else
	{
		size = stoi(size1);
		price = stoi(price1);
		quantity = stoi(quantity1);
		try
		{
			this->adminService.addCoat(size, colour, price, quantity, photograph);
		}
		catch (ServiceException& es)
		{
			std::cout << es.what() << endl;
		}
	}
	
}

int UI::addCoatToBasket(int pos)
{
	Coat newCoat = adminService.getRepo().getArray()[pos];
	this->adminService.updateCoatQuantity(newCoat.getSize(), newCoat.getQuantity() - 1);
	int elem = adminService.getRepo().FindElemBySize(pos);
	bool added = false;
	int i = 0;
	while (i < userService.getRepo().getSize())
	{
		if (newCoat.getSize() == userService.getRepo().getArray()[i].getSize())
		{
			this->userService.updateCoatQuantity(i, userService.getRepo().getArray()[i].getQuantity() + 1);
			added = true;
			break;
		}
		i++;
	}
	if(added == false)
		this->userService.addCoatToBasket(newCoat.getSize(), newCoat.getColour(), newCoat.getPrice(), 1, newCoat.getPhotograph());
	return newCoat.getPrice();
}

void UI::removeCoat()
{
	int size;
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
	auto repo = adminService.getRepo();
	for (auto i : repo.getArray())
	{
		cout << i;
	}
}

void UI::printAllCoatsBasket()
{
	auto basket = userService.getRepo();
	if (basket.getSize() == 0)
		std::cout << "No coats in the shopping basket yet.";
	else
	{
		for (auto i : basket.getArray())
		{
			cout << i;
		}
	}
}

void UI::printBasketFile(std::string fileType)
{
	while (true)
	{
		if (fileType == "csv")
		{
			system("notepad.exe 'Basket.csv'");
			break;
		}
		else if (fileType == "html")
		{
			system("opera.exe 'Basket.html'");
			break;
		}
		else
		{
			cout << "ERROR: Wrong file type!";
		}
	}
}

int UI::searchCoat(int size)
{
	Repository repo = adminService.getRepo();
	vector<Coat> coats = repo.getArray();
	int elem = repo.FindElemBySize(size);
	if (elem == -1)
		cout << "Error, the coat does not exist!";
	else
		cout << coats[elem];
	return elem;
}

void UI::printCoat(int pos)
{
	cout << adminService.getRepo().getArray()[pos];
}

void UI::printCoatUser()
{
	int size = 0;
	int price = 0;
	while (true)
	{
		cout << "Type the size of the coat that you want to see.\n";
		cin >> size;
		int elemSize = searchCoat(size);
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