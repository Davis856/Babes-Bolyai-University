#pragma once
#include "Repository.h"
#include <memory>
#include "UndoRedo.h"

class AdminService
{
private:
	Repository& repo;
	std::vector<std::shared_ptr<UndoRedoAction>> undoAdmin;
	std::vector<std::shared_ptr<UndoRedoAction>> redoAdmin;

public:
	/// <summary>
	/// Constructor for the admin service
	/// </summary>
	/// <param name="repo">The repository on which the class service operates</param>
	AdminService(Repository& repo);

	/// <summary>
	/// Adds a new coat to the repository
	/// </summary>
	/// <param name="size">The size of the coat</param>
	/// <param name="colour">The colour of the coat</param>
	/// <param name="price">The price of the coat</param>
	/// <param name="quantity">The quantity for the coat</param>
	/// <param name="photograph">The photograph of the coat</param>
	void addCoat(int size, std::string colour, int price, int quantity, std::string photograph);

	/// <summary>
	/// Remove a certain coat from the repository
	/// </summary>
	/// <param name="size">The size of the coat to be removed</param>
	void removeCoat(int size);

	/// <summary>
	/// Updates the title of a coat from the repository
	/// </summary>
	/// <param name="size">The size of the coat to be updated</param>
	/// <param name="newSize">The new size to be given to the coat</param>
	void updateCoatSize(int size, int newSize);

	/// <summary>
	/// Updates the genre of a coat from the repo
	/// </summary>
	/// <param name="size">The size of the coat to update</param>
	/// <param name="newColour">The new genre to be given to a coat</param>
	void updateCoatColour(int size, std::string newColour);

	/// <summary>
	/// Updates the year a coat has been released
	/// </summary>
	/// <param name="size"></param>
	/// <param name="newPrice"></param>
	void updateCoatPrice(int size, int newPrice);

	/// <summary>
	/// Updates the number of likes a coat has been given
	/// </summary>
	/// <param name="size">The size of the coat to be updated</param>
	/// <param name="newQuantity">The new quantity to be given to a coat</param>
	void updateCoatQuantity(int size, int newQuantity);

	/// <summary>
	/// Update the photograph associated to a given coat
	/// </summary>
	/// <param name="size">The name of the coat to be updated</param>
	/// <param name="newPhotograph">The new photograph to be attributed to the coat</param>
	void updateCoatPhotograph(int size, std::string newPhotograph);

	/// <summary>
	/// Prints the content of the repo
	/// </summary>
	/// <returns></returns>
	Repository getRepo() const;

	void undoLastAction();
	void redoLastAction();
	void clearUndoRedo();

	void getFiltered(std::vector<Coat>& validCoats, int priceFilter);
};

class ServiceException : public std::exception {
private:
	std::string message;
public:
	explicit ServiceException(std::string& _message);

	const char* what() const noexcept override;
};