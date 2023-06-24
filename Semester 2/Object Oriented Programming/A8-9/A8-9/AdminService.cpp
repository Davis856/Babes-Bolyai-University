#include "AdminService.h"
#include "Validator.h"
#include <exception>
#include <fstream>
#include <iostream>


ServiceException::ServiceException(std::string& _message) : message(_message) {}

const char* ServiceException::what() const noexcept {
	return message.c_str();
}

AdminService::AdminService(Repository& repository) : repo{ repository } {}

void AdminService::addCoat(int size, std::string colour, int price, int quantity, std::string photograph)
{
	Coat newCoat = Coat(size, colour, price, quantity, photograph);

	bool dupli = false;
	int i = 0;

	while (i < this->repo.getSize())
	{
		if (this->repo.getArray()[i] == newCoat)
			dupli = true;
		i++;
	}
	if (dupli)
	{
		std::string error;
		error += "A coat of this parameteres already exists.";
		throw ServiceException(error);
	}
	this->repo.addCoat(newCoat);
}

void AdminService::removeCoat(int size)
{
	int pos = this->repo.FindElemBySize(size);
	if (pos >= this->repo.getSize())
	{
		std::string error;
		error += "Coat does not exist.";
		throw ServiceException(error);
	}

	this->repo.removeCoat(pos);
}

void AdminService::updateCoatSize(int size, int newSize)
{
	if (!Validator::validCoatSize(newSize))
	{
		std::string error;
		error += "Invalid coat.";
		throw ServiceException(error);
	}
		
	int pos = this->repo.FindElemBySize(size);

	if (pos > this->repo.getSize())
	{
		std::string error;
		error += "Coat does not exist.";
		throw ServiceException(error);
	}
	this->repo.updateSize(pos, newSize);
}

void AdminService::updateCoatColour(int size, std::string newColour)
{
	if (!Validator::validCoatColour(newColour))
	{
		std::string error;
		error += "Invalid coat.";
		throw ServiceException(error);
	}
	int pos = this->repo.FindElemBySize(size);

	if(pos > this->repo.getSize())
	{
		std::string error;
		error += "Coat does not exist.";
		throw ServiceException(error);
	}
	this->repo.updateColour(pos, newColour);
}

void AdminService::updateCoatPrice(int size, int newPrice)
{
	if (!Validator::validCoatPrice(newPrice))
	{
		std::string error;
		error += "Invalid coat.";
		throw ServiceException(error);
	}
	int pos = this->repo.FindElemBySize(size);

	if (pos > this->repo.getSize())
	{
		std::string error;
		error += "Coat does not exist.";
		throw ServiceException(error);
	}
	this->repo.updatePrice(pos, newPrice);
}

void AdminService::updateCoatQuantity(int size, int newQuantity)
{
	if (!Validator::validCoatQuantity(newQuantity))
	{
		std::string error;
		error += "Invalid coat.";
		throw ServiceException(error);
	}
	int pos = this->repo.FindElemBySize(size);

	if (pos > this->repo.getSize())
	{
		std::string error;
		error += "Coat does not exist.";
		throw ServiceException(error);
	}
	this->repo.updateQuantity(pos, newQuantity);
}

void AdminService::updateCoatPhotograph(int size, std::string newPhotograph)
{
	if (!Validator::validCoatPhotograph(newPhotograph))
	{
		std::string error;
		error += "Invalid coat.";
		throw ServiceException(error);
	}
	int pos = this->repo.FindElemBySize(size);

	if (pos > this->repo.getSize())
	{
		std::string error;
		error += "Coat does not exist.";
		throw ServiceException(error);
	}
	this->repo.updatePhotograph(pos, newPhotograph);
}

Repository AdminService::getRepo() const
{
	return this->repo;
}

void AdminService::InitializeRepo()
{
	addCoat(1, "Blue", 50, 20, "https://google.ro");
	addCoat(5, "Yellow", 30, 70, "https://google.ro");
	addCoat(6, "Green", 80, 90, "https://google.ro");
	addCoat(3, "Blue", 10, 20, "https://google.ro");
	addCoat(4, "Black", 50, 60, "https://google.ro");
	addCoat(2, "White", 30, 20, "https://google.ro");
	addCoat(8, "Purple", 60, 40, "https://google.ro");
	addCoat(10, "Orange", 80, 40, "https://google.ro");
	addCoat(7, "Violet", 20, 100, "https://google.ro");
	addCoat(12, "Magenta", 60, 200, "https://google.ro");
}

