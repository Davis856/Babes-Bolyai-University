#include "Coat.h"
#include <Windows.h>
#include <shellapi.h>
#include <iostream>
#include <vector>

using namespace std;

Coat::Coat(int size, const std::string& colour, int price, int quantity, const std::string& photograph) : size{ size }, colour{ colour }, price{ price }, quantity{ quantity }, photograph{ photograph } {}


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

istream& operator>>(istream& is, Coat& coat)
{
	// use reading with getline and then tokenisation if you want to validate the number of tokens

	if (is.eof())
		is.setstate(ios_base::failbit); // operator bool returns true for eof => enforce false to terminate the loop
	else
	{
		string comma;
		is >> coat.size;
		getline(is, comma, ',');
		getline(is, coat.colour, ',');
		is >> coat.price;
		getline(is, comma, ',');
		is >> coat.quantity;
		getline(is, comma, ',');
		getline(is, coat.photograph, '\n');
	}
	return is;
}