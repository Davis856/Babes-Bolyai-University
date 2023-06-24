#pragma once

#include <vector>
#include "Coat.h"
#include <string>
#include <iostream>

class Basket // User Basket
{
protected:
	vector<Coat> basket;
	std::string filename;

public:


	/*
		Constructor with parameters.
		Initializes an object of type repository, by reading data from the given file.
		Throws: FileException - if the file cannot be opened.
	*/
	Basket(const std::string& filename);

	Basket();

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
	void updateQuantity(int position, int newQuantity);

	/// <summary>
	/// Find the position of the element which we want to search for
	/// </summary>
	/// <param name="size">The size of the coat to be removed</param>
	/// <returns>The position of the coat</returns>
	int FindElemBySize(int size);

	virtual int getSize();
	virtual vector<Coat> getArray();

private:
	void readFromFile();
	virtual void writeToFile();

};

class UserException : public std::exception {
private:
	std::string message;
public:
	explicit UserException(std::string& _message);

	const char* what() const noexcept override;
};