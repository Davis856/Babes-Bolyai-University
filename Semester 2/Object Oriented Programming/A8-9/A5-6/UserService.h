#pragma once

#include "Basket.h"

class UserService
{
private:
	Basket& repo;

public:
	/// <summary>
	/// Constructor for the admin service
	/// </summary>
	/// <param name="repo">The Repository on which the class service operates</param>
	UserService(Basket& repo);

	/// <summary>
	/// Adds a new coat to the Repository
	/// </summary>
	/// <param name="size">The size of the coat</param>
	/// <param name="colour">The colour of the coat</param>
	/// <param name="price">The price of the coat</param>
	/// <param name="quantity">The quantity for the coat</param>
	/// <param name="photograph">The photograph of the coat</param>
	void addCoatToBasket(size_t size, std::string colour, size_t price, size_t quantity, std::string photograph);

	/// <summary>
	/// Updates the number of likes a coat has been given
	/// </summary>
	/// <param name="size">The size of the coat to be updated</param>
	/// <param name="newQuantity">The new quantity to be given to a coat</param>
	void updateCoatQuantity(size_t size, size_t newQuantity);

	/// <summary>
	/// Prints the content of the repo
	/// </summary>
	/// <returns></returns>
	Basket getRepo() const;
};