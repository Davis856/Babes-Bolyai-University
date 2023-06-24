#include "Repository.h"
#include <string>
#include <fstream>

RepositoryException::RepositoryException(std::string& _message) : message(_message) {}

const char* RepositoryException::what() const noexcept {
	return message.c_str();
}

Repository::Repository(const std::string& filename)
{
	this->filename = filename;
	this->readFromFile();
}

void Repository::addCoat(const Coat& element)
{
	int exists = this->FindElemBySize(element.getSize());
	if (exists != -1)
	{
		std::string error;
		error += std::string("The coat already exists");
		if (!error.empty())
		{
			throw RepositoryException(error);
		}
	}
	this->Coats.push_back(element);
	this->writeToFile();
}

void Repository::removeCoat(int position)
{
	this->Coats.erase(this->Coats.begin() + position);
	this->writeToFile();
}

void Repository::updateSize(int position, int newSize)
{
	this->Coats[position].setSize(newSize);
	this->writeToFile();
}

void Repository::updateColour(int position, std::string newColour)
{
	this->Coats[position].setColour(newColour);
	this->writeToFile();
}

void Repository::updatePrice(int position, int newPrice)
{
	this->Coats[position].setPrice(newPrice);
	this->writeToFile();
}

void Repository::updateQuantity(int position, int newQuantity)
{
	this->Coats[position].setQuantity(newQuantity);
	this->writeToFile();
}

void Repository::updatePhotograph(int position, std::string newPhotograph)
{
	this->Coats[position].setPhotograph(newPhotograph);
	this->writeToFile();
}

int Repository::FindElemBySize(int size) const
{
	int pos = -1;
	int i = 0;
	while (i < this->getSize())
	{
		if (this->Coats[i].getSize() == size)
		{
			pos = i;
			break;
		}
		i++;
	}	
	return pos;
}

int Repository::getSize() const
{
	return this->Coats.size();
}

std::vector<Coat> Repository::getArray() const
{
	return this->Coats;
}

void Repository::readFromFile()
{
	std::ifstream file(this->filename);

	Coat coat;
	while (file >> coat)
		this->Coats.push_back(coat);

	file.close();
}

void Repository::writeToFile()
{
	std::ofstream file(this->filename);

	for (auto coat : this->Coats)
	{
		file << coat;
	}

	file.close();
}

void Repository::InitializeRepo()
{
	std::string filename = "Initialize.txt";
	if (!filename.empty()) {
		Coat coatFromFile;
		std::ifstream fin(filename);
		while (fin >> coatFromFile) {
			std::cout << coatFromFile;
			if (std::find(this->Coats.begin(), this->Coats.end(), coatFromFile) ==
				this->Coats.end())
				this->Coats.push_back(coatFromFile);
		}
		fin.close();
	}
}