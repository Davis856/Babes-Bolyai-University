#include "Validator.h"
#include <regex>

bool Validator::validCoatSize(size_t size)
{
	return size >= 0;
}

bool Validator::validCoatColour(std::string colour)
{
	return !colour.empty();
}

bool Validator::validCoatPrice(size_t price)
{
	return price >= 0;
}

bool Validator::validCoatQuantity(size_t quantity)
{
	return quantity >= 0;
}

bool Validator::validCoatPhotograph(std::string photograph)
{
	return std::regex_match(photograph, std::regex("(^https:\/\/)?([a-zA-Z])+\.([a-z]{2,})(\/(.)+)?"));
}
