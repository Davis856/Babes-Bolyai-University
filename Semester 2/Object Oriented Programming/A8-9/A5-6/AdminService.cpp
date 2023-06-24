#include "AdminService.h"
#include "Validator.h"
#include <exception>

AdminService::AdminService(Repository& repository) : repo{ repository } {}

void AdminService::addCoat(size_t size, std::string colour, size_t price, size_t quantity, std::string photograph)
{

	Coat newCoat = Coat(size, colour, price, quantity, photograph);

	bool dupli = false;
	for (size_t i = 0; i < this->repo.getSize(); ++i)
		if (this->repo[i] == newCoat) dupli = true;

	if (dupli) throw std::exception("A coat of this parameters already exists!");

	this->repo.addCoat(newCoat);
}

void AdminService::removeCoat(size_t size)
{
	size_t pos = this->repo.FindElemBySize(size);
	if (pos >= this->repo.getSize())
		throw std::exception("Coat does not exist");

	this->repo.removeCoat(pos);
}

void AdminService::updateCoatSize(size_t size, size_t newSize)
{
	if (!Validator::validCoatSize(newSize)) throw std::exception("Invalid coat");
	size_t pos = this->repo.FindElemBySize(size);

	if (pos > this->repo.getSize()) throw std::exception("Coat does not exist");
	this->repo.updateSize(pos, newSize);
}

void AdminService::updateCoatColour(size_t size, std::string newColour)
{
	if (!Validator::validCoatColour(newColour)) throw std::exception("Invalid coat");
	size_t pos = this->repo.FindElemBySize(size);

	if (pos > this->repo.getSize()) throw std::exception("Coat does not exist");
	this->repo.updateColour(pos, newColour);
}

void AdminService::updateCoatPrice(size_t size, size_t newPrice)
{
	if (!Validator::validCoatPrice(newPrice)) throw std::exception("Invalid coat");
	size_t pos = this->repo.FindElemBySize(size);

	if (pos > this->repo.getSize()) throw std::exception("Coat does not exist");
	this->repo.updatePrice(pos, newPrice);
}

void AdminService::updateCoatQuantity(size_t size, size_t newQuantity)
{
	if (!Validator::validCoatQuantity(newQuantity)) throw std::exception("Invalid coat");
	size_t pos = this->repo.FindElemBySize(size);

	if (pos > this->repo.getSize()) throw std::exception("Coat does not exist");
	this->repo.updateQuantity(pos, newQuantity);
}

void AdminService::updateCoatPhotograph(size_t size, std::string newPhotograph)
{
	if (!Validator::validCoatPhotograph(newPhotograph)) throw std::exception("Invalid coat");
	size_t pos = this->repo.FindElemBySize(size);

	if (pos > this->repo.getSize()) throw std::exception("Coat does not exist");
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

