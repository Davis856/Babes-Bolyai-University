#include "UserService.h"
#include <exception>

UserService::UserService(Basket& basket) : repo{ basket } {}

void UserService::addCoatToBasket(size_t size, std::string colour, size_t price, size_t quantity, std::string photograph)
{

	Coat newCoat = Coat(size, colour, price, quantity, photograph);

	this->repo.addCoatToBasket(newCoat);
}

void UserService::updateCoatQuantity(size_t size, size_t newQuantity)
{
	this->repo.updateQuantity(size, newQuantity);
}


Basket UserService::getRepo() const
{
	return this->repo;
}

