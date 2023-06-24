#include "Repository.h"
#include <sstream>

Repository::Repository() : Coats{ }{}

Repository::Repository(size_t maxSize) :
	Coats{ new DynamicVector<Coat>(maxSize) }
{
}

Repository::Repository(const Repository& other) :
	Coats{ new DynamicVector<Coat>(*other.Coats) }
{
}

Repository::~Repository()
{
	delete this->Coats;
	this->Coats = nullptr;
}

Repository& Repository::operator=(const Repository& other)
{
	if (this == &other) return *this;

	if (this->Coats == nullptr) this->Coats = new DynamicVector<Coat>();
	*this->Coats = *other.Coats;

	return *this;
}

Coat& Repository:: operator[](size_t position)
{
	return (*this->Coats)[position];
}

std::ostream& operator<<(std::ostream& os, const Repository& repo)
{
	os << *repo.Coats;
	return os;
}

void Repository::addCoat(const Coat& element)
{
	this->Coats->add(element);
}

void Repository::removeCoat(size_t position)
{
	this->Coats->remove(position);
}

void Repository::updateSize(size_t position, size_t newSize)
{
	(*this->Coats)[position].setSize(newSize);
}

void Repository::updateColour(size_t position, std::string newColour)
{
	(*this->Coats)[position].setColour(newColour);
}

void Repository::updatePrice(size_t position, size_t newPrice)
{
	(*this->Coats)[position].setPrice(newPrice);
}

void Repository::updateQuantity(size_t position, size_t newQuantity)
{
	(*this->Coats)[position].setQuantity(newQuantity);
}

void Repository::updatePhotograph(size_t position, std::string newPhotograph)
{
	(*this->Coats)[position].setPhotograph(newPhotograph);
}

size_t Repository::FindElemBySize(size_t size) const
{
	size_t pos = -1;
	for(size_t i=0; i<this->getSize(); ++i)
		if ((*this->Coats)[i].getSize() == size)
		{
			pos = i;
			break;
		}
	return pos;
}

size_t Repository::getSize() const
{
	return this->Coats->getSize();
}

DynamicVector<Coat> Repository::getArray() const
{
	return *this->Coats;
}