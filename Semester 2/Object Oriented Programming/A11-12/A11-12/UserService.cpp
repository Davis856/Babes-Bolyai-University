#include "UserService.h"
#include <exception>
#include "CSVBasket.h"
#include "HTMLBasket.h"
#include <algorithm>

UserService::UserService(Basket* basket) : repo{ basket } {}

void UserService::addCoatToBasket(int size, std::string colour, int price, int quantity, std::string photograph)
{

	Coat newCoat = Coat(size, colour, price, quantity, photograph);

	this->repo->addCoatToBasket(newCoat);

    std::shared_ptr<UndoRedoAction> action = std::make_shared<UndoRedoUser>(dog, this->repository, this->userRepository);
    this->undoUser.push_back(action);
}

void UserService::updateCoatQuantity(int size, int newQuantity)
{
	this->repo->updateQuantity(size, newQuantity);
}


Basket UserService::getRepo() const
{
	return *this->repo;
}

void UserService::repositoryType(const std::string& fileType) 
{
    if (fileType == "csv") {
        std::vector<Coat> userVector;
        std::string userFile = "Basket.csv";
        auto* repo = new CSVBasket{ userVector, userFile };
        this->repo = repo;
    }
    else if (fileType == "html") {
        std::vector<Coat> userVector;
        std::string userFile = "Basket.html";
        auto* repo = new HTMLBasket{ userVector, userFile };
        this->repo = repo;
    }
    else {
        std::string error;
        error += std::string("The filename is invalid!");
        if (!error.empty())
            throw UserException(error);
    }
}

std::string& UserService::getFileService() {
    return this->repo->getFilename();
}

void UserService::getFiltered(std::vector<Coat>& valid_Coats, int priceFilter) {
    std::vector<Coat> data;
    data = this->repo->getArray();
    std::copy_if(data.begin(), data.end(), std::back_inserter(valid_Coats), [&priceFilter](Coat& Coat) { return Coat.getPrice() == priceFilter; });
}

void UserService::undoLastAction() {
    if (this->undoUser.empty()) {
        std::string error;
        error += std::string("No more undoes left!");
        if (!error.empty())
            throw RepositoryException(error);
    }
    this->undoUser.back()->undo();
    this->redoUser.push_back(this->undoUser.back());
    this->undoUser.pop_back();
}

void UserService::redoLastAction() {
    if (this->redoUser.empty()) {
        std::string error;
        error += std::string("No more redoes left!");
        if (!error.empty())
            throw RepositoryException(error);
    }
    this->redoUser.back()->redo();
    this->undoUser.push_back(this->redoUser.back());
    this->redoUser.pop_back();
}

void UserService::clearUndoRedo() {
    this->undoUser.clear();
    this->redoUser.clear();
}