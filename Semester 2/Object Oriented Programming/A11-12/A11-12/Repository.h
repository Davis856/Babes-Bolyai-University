#pragma once
#include <vector>
#include "Coat.h"
#include <string>
#include <iostream>

class Repository
{
private:
	std::vector<Coat> Coats;
	std::string filename;

public:

	/*
		Constructor with parameters.
		Initializes an object of type repository, by reading data from the given file.
		Throws: FileException - if the file cannot be opened.
	*/
	Repository(const std::string& filename);

	/// <summary>
	/// Adds a new coat to the repository
	/// </summary>
	/// <param name="coat">The coat to be added</param>
	void addCoat(const Coat& coat);

	/// <summary>
	/// Removes a coat from the repo
	/// </summary>
	/// <param name="position">The position of the element to be removed</param>
	void removeCoat(int position);

	/// <summary>
	/// Update the title of a coat
	/// </summary>
	/// <param name="position">The position of the coat to be changed</param>
	/// <param name="newSize">The new size to be given to the coat</param>
	void updateSize(int position, int newSize);

	/// <summary>
	/// Update the genre of a coat
	/// </summary>
	/// <param name="position">The position of the coat to be changed</param>
	/// <param name="newColour">The new colour to be given to the coat</param>
	void updateColour(int position, std::string newColour);

	/// <summary>
	/// Update the year the coat has been released 
	/// </summary>
	/// <param name="position">The position of the coat to be updated</param>
	/// <param name="newPrice">The new price to be given to the coat</param>
	void updatePrice(int position, int newPrice);

	/// <summary>
	/// Update the number of likes of a coat
	/// </summary>
	/// <param name="position">The postition of the coat to be updated</param>
	/// <param name="newQuantity">The new quantity to be given the coat</param>
	void updateQuantity(int position, int newQuantity);

	/// <summary>
	/// Update the trailer of a coat
	/// </summary>
	/// <param name="position">The position of the coat to be updated</param>
	/// <param name="newPhotograph">THe new photograph to be given to a certain coat</param>
	void updatePhotograph(int position, std::string newPhotograph);

	/// <summary>
	/// Find the position of the element which we want to search for
	/// </summary>
	/// <param name="size">The size of the coat to be removed</param>
	/// <returns>The position of the coat</returns>
	int FindElemBySize(int size) const;

	void InitializeRepo();

	int getSize() const;
	std::vector<Coat> getArray() const;


private:
	void readFromFile();
	void writeToFile();
};


class RepositoryException : public std::exception {
private:
	std::string message;
public:
	explicit RepositoryException(std::string& _message);

	const char* what() const noexcept override;
};