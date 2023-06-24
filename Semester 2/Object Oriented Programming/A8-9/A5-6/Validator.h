#pragma once
#include "Coat.h"

class Validator
{
public:
	static bool validCoatAttr(size_t size, std::string colour, size_t price, size_t quantity, std::string photograph);
	static bool validCoatSize(size_t size);
	static bool validCoatColour(std::string colour);
	static bool validCoatPrice(size_t price);
	static bool validCoatQuantity(size_t quantity);
	static bool validCoatPhotograph(std::string photograph);
};