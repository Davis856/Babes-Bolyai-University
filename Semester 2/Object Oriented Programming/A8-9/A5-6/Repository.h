#pragma once
#include "DynamicVector.h"
#include "Coat.h"
#include <string>
#include <iostream>

class Repository
{
private:
	DynamicVector<Coat>* Coats;

public:
	/// <summary>
	/// Default constructor for coat repo
	/// </summary>
	Repository();

	/// <summary>
	/// Constructor which initialize the repo with a dynamic array of a given size
	/// </summary>
	/// <param name="maxSize">The capacity of the dynamic array</param>
	Repository(size_t maxSize);

	/// <summary>
	/// Copy constructor for a coat repo
	/// </summary>
	/// <param name="other">The repo to copy to</param>
	Repository(const Repository& other);

	/// <summary>
	/// Destructor for a Coat repo
	/// </summary>
	~Repository();

	/// <summary>
	/// Indexing operator for coat repository
	/// </summary>
	/// <param name="position">The position of the element to be returned</param>
	/// <returns>The element</returns>
	Coat& operator[](size_t position);

	/// <summary>
	/// Copy a repo to another
	/// </summary>
	/// <param name="other">The repo to be copied</param>
	/// <returns>An object with the same elements as the existing one</returns>
	Repository& operator=(const Repository& other);

	/// <summary>
	/// Insertion operator for the repository class
	/// </summary>
	/// <param name="os">The stream object to write to</param>
	/// <param name="repo">The repo to be written</param>
	/// <returns>A stream containing the elements of the repository</returns>
	friend std::ostream& operator<<(std::ostream& os, const Repository& repo);

	/// <summary>
	/// Adds a new coat to the repository
	/// </summary>
	/// <param name="coat">The coat to be added</param>
	void addCoat(const Coat& coat);

	/// <summary>
	/// Removes a coat from the repo
	/// </summary>
	/// <param name="position">The position of the element to be removed</param>
	void removeCoat(size_t position);

	/// <summary>
	/// Update the title of a coat
	/// </summary>
	/// <param name="position">The position of the coat to be changed</param>
	/// <param name="newSize">The new size to be given to the coat</param>
	void updateSize(size_t position, size_t newSize);

	/// <summary>
	/// Update the genre of a coat
	/// </summary>
	/// <param name="position">The position of the coat to be changed</param>
	/// <param name="newColour">The new colour to be given to the coat</param>
	void updateColour(size_t position, std::string newColour);

	/// <summary>
	/// Update the year the coat has been released 
	/// </summary>
	/// <param name="position">The position of the coat to be updated</param>
	/// <param name="newPrice">The new price to be given to the coat</param>
	void updatePrice(size_t position, size_t newPrice);

	/// <summary>
	/// Update the number of likes of a coat
	/// </summary>
	/// <param name="position">The postition of the coat to be updated</param>
	/// <param name="newQuantity">The new quantity to be given the coat</param>
	void updateQuantity(size_t position, size_t newQuantity);

	/// <summary>
	/// Update the trailer of a coat
	/// </summary>
	/// <param name="position">The position of the coat to be updated</param>
	/// <param name="newPhotograph">THe new photograph to be given to a certain coat</param>
	void updatePhotograph(size_t position, std::string newPhotograph);

	/// <summary>
	/// Find the position of the element which we want to search for
	/// </summary>
	/// <param name="size">The size of the coat to be removed</param>
	/// <returns>The position of the coat</returns>
	size_t FindElemBySize(size_t size) const;

	size_t getSize() const;
	DynamicVector<Coat> getArray() const;

};