#pragma once

#pragma once
#include "DynamicVector.h"
#include "Coat.h"
#include <string>
#include <iostream>

class Basket // User Basket
{
private:
	DynamicVector<Coat>* basket;

public:
	/// <summary>
	/// Default constructor for coat basket
	/// </summary>
	Basket();

	/// <summary>
	/// Constructor which initialize the basket with a dynamic array of a given size
	/// </summary>
	/// <param name="maxSize">The capacity of the dynamic array</param>
	Basket(size_t maxSize);

	/// <summary>
	/// Copy constructor for a coat repo
	/// </summary>
	/// <param name="other">The repo to copy to</param>
	Basket(const Basket& other);

	/// <summary>
	/// Destructor for a Coat basket
	/// </summary>
	~Basket();

	/// <summary>
	/// Insertion operator for the Basket class
	/// </summary>
	/// <param name="os">The stream object to write to</param>
	/// <param name="repo">The repo to be written</param>
	/// <returns>A stream containing the elements of the Basket</returns>
	friend std::ostream& operator<<(std::ostream& os, const Basket& repo);

	/// <summary>
	/// Adds a new coat to the Basket
	/// </summary>
	/// <param name="coat">The coat to be added</param>
	void addCoatToBasket(const Coat& coat);

	/// <summary>
	/// Update the number of likes of a coat
	/// </summary>
	/// <param name="position">The postition of the coat to be updated</param>
	/// <param name="newQuantity">The new quantity to be given the coat</param>
	void updateQuantity(size_t position, size_t newQuantity);

	/// <summary>
	/// Find the position of the element which we want to search for
	/// </summary>
	/// <param name="size">The size of the coat to be removed</param>
	/// <returns>The position of the coat</returns>
	size_t FindElemBySize(size_t size) const;

	size_t getSize() const;
	DynamicVector<Coat> getArray() const;

};