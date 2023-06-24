#include "Coat.h"
#include <sstream>
#include <Windows.h>
#include <shellapi.h>

Coat::Coat(size_t size, const std::string& colour, size_t price, size_t quantity, const std::string& photograph) : size{ size }, colour{ colour }, price{ price }, quantity{ quantity }, photograph{ photograph } {}


Coat::~Coat()
{
}

bool Coat::operator==(const Coat& other) const
{
	return this->size == other.size;
}

std::ostream& operator<<(std::ostream& os, const Coat& coat)
{
	return os << "Size: " << coat.size << " | Colour: " << coat.colour << " | Price: " << coat.price << "$ | Quantity: "
		<< coat.quantity << " | Photograph: " << coat.photograph << "\n";
}