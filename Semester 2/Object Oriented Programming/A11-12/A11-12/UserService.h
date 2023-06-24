#pragma once

#include "Basket.h"
#include <memory>
#include "UndoRedo.h"

class UserService
{
private:
	Basket* repo;
	std::vector<std::shared_ptr<UndoRedoAction>> undoUser;
	std::vector<std::shared_ptr<UndoRedoAction>> redoUser;

public:
	/// <summary>
	/// Constructor for the admin service
	/// </summary>
	/// <param name="repo">The Repository on which the class service operates</param>
	UserService(Basket* repo);

	/// <summary>
	/// Adds a new coat to the Repository
	/// </summary>
	/// <param name="size">The size of the coat</param>
	/// <param name="colour">The colour of the coat</param>
	/// <param name="price">The price of the coat</param>
	/// <param name="quantity">The quantity for the coat</param>
	/// <param name="photograph">The photograph of the coat</param>
	void addCoatToBasket(int size, std::string colour, int price, int quantity, std::string photograph);

	/// <summary>
	/// Updates the number of likes a coat has been given
	/// </summary>
	/// <param name="size">The size of the coat to be updated</param>
	/// <param name="newQuantity">The new quantity to be given to a coat</param>
	void updateCoatQuantity(int size, int newQuantity);

	/// <summary>
	/// Prints the content of the repo
	/// </summary>
	/// <returns></returns>
	Basket getRepo() const;

	void repositoryType(const std::string& fileType);
	std::string& getFileService();

	void undoLastAction();
	void redoLastAction();
	void clearUndoRedo();

	void getFiltered(std::vector<Coat>& valid_Coats, int priceFilter);

};