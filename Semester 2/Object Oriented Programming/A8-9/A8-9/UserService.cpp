#include "UserService.h"
#include <exception>
#include "CSVBasket.h"
#include "HTMLBasket.h"

UserService::UserService(Basket* basket) : repo{ basket } {}

void UserService::addCoatToBasket(int size, std::string colour, int price, int quantity, std::string photograph)
{

	Coat newCoat = Coat(size, colour, price, quantity, photograph);

	this->repo->addCoatToBasket(newCoat);
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