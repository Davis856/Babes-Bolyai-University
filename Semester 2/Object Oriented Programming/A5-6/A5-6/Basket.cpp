#include "Basket.h"
#include <sstream>

Basket::Basket() : basket{ }{}

Basket::Basket(size_t maxSize) :
	basket{ new DynamicVector<Coat>(maxSize) }
{
}

Basket::Basket(const Basket& other) :
	basket{ new DynamicVector<Coat>(*other.basket) }
{
}

Basket::~Basket()
{
	delete this->basket;
	this->basket = nullptr;
}

std::ostream& operator<<(std::ostream& os, const Basket& repo)
{
	os << *repo.basket;
	return os;
}

void Basket::addCoatToBasket(const Coat& element)
{
	this->basket->add(element);
}

void Basket::updateQuantity(size_t position, size_t newQuantity)
{
	(*this->basket)[position].setQuantity(newQuantity);
}

size_t Basket::FindElemBySize(size_t size) const
{
	size_t pos = 0;
	for (size_t i = 0; i < this->getSize(); ++i)
		if ((*this->basket)[i].getSize() == size)
		{
			pos = i;
			break;
		}
	return pos;
}

size_t Basket::getSize() const
{
	return this->basket->getSize();
}

DynamicVector<Coat> Basket::getArray() const
{
	return *this->basket;
}