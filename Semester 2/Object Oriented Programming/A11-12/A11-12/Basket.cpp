#include "Basket.h"
#include <string>
#include <fstream>

UserException::UserException(std::string& _message) : message(_message) {}

const char* UserException::what() const noexcept {
	return message.c_str();
}

Basket::Basket(const std::string& filename)
{
	this->filename = filename;
	this->readFromFile();
}

Basket::Basket() = default;

void Basket::addCoatToBasket(const Coat& element)
{
	this->basket.push_back(element);
	this->writeToFile();
}

void Basket::updateQuantity(int position, int newQuantity)
{
	this->basket[position].setQuantity(newQuantity);
	this->writeToFile();
}

int Basket::FindElemBySize(int size)
{
	int pos = -1;
	int i = 0;
	while (i < this->getSize())
	{
		if (this->basket[i].getSize() == size)
		{
			pos = i;
			break;
		}
		i++;
	}
	return pos;
}

int Basket::getSize()
{
	return this->basket.size();
}

std::vector<Coat> Basket::getArray()
{
	return this->basket;
}

void Basket::readFromFile()
{
	std::ifstream file(this->filename);

	//if (!file.is_open())
		//throw FileException("The file could not be opened!");

	Coat coat;
	while (file >> coat)
		this->basket.push_back(coat);

	file.close();
}

void Basket::writeToFile()
{
	std::ofstream file(this->filename);
	//if (!file.is_open())
		//throw FileException("The file could not be opened!");

	for (auto coat : this->basket)
	{
		file << coat;
	}

	file.close();
}

std::string& Basket::getFilename()
{
	return this->filename;
}