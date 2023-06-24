#include "AdminService.h"
#include "Validator.h"
#include <exception>
#include <fstream>
#include <iostream>
#include <algorithm>


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
	std::shared_ptr<UndoRedoAction> action = std::make_shared<UndoRedoAdd>(newCoat, this->repo);
	this->undoAdmin.push_back(action);
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

	std::shared_ptr<UndoRedoAction> action = std::make_shared<UndoRedoRemove>(pos, this->repo);
	this->undoAdmin.push_back(action);
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

	std::shared_ptr<UndoRedoAction> action = std::make_shared<UndoRedoUpdate>(pos, newSize, this->repo);
	this->undoAdmin.push_back(action);
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

	std::shared_ptr<UndoRedoAction> action = std::make_shared<UndoRedoUpdate>(old_dog, new_dog, this->repository);
	this->undoAdmin.push_back(action);
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

	std::shared_ptr<UndoRedoAction> action = std::make_shared<UndoRedoUpdate>(old_dog, new_dog, this->repository);
	this->undoAdmin.push_back(action);
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

	std::shared_ptr<UndoRedoAction> action = std::make_shared<UndoRedoUpdate>(old_dog, new_dog, this->repository);
	this->undoAdmin.push_back(action);
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

	std::shared_ptr<UndoRedoAction> action = std::make_shared<UndoRedoUpdate>(old_dog, new_dog, this->repository);
	this->undoAdmin.push_back(action);
}

Repository AdminService::getRepo() const
{
	return this->repo;
}

void AdminService::getFiltered(std::vector<Coat>& valid_Coats, int priceFilter) {
	std::vector<Coat> data;
	data = this->repo.getArray();
	std::copy_if(data.begin(), data.end(), std::back_inserter(valid_Coats), [&priceFilter](Coat& Coat) { return Coat.getPrice() == priceFilter; });
}

void AdminService::undoLastAction() {
	if (this->undoAdmin.empty()) {
		std::string error;
		error += std::string("No more undoes left!");
		if (!error.empty())
			throw RepositoryException(error);
	}
	this->undoAdmin.back()->undo();
	this->redoAdmin.push_back(this->undoAdmin.back());
	this->undoAdmin.pop_back();
}

void AdminService::redoLastAction() {
	if (this->redoAdmin.empty()) {
		std::string error;
		error += std::string("No more redoes left!");
		if (!error.empty())
			throw RepositoryException(error);
	}
	this->redoAdmin.back()->redo();
	this->undoAdmin.push_back(this->redoAdmin.back());
	this->redoAdmin.pop_back();
}

void AdminService::clearUndoRedo() {
	this->undoAdmin.clear();
	this->redoAdmin.clear();
}
