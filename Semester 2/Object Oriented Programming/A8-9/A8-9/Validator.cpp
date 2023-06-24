#include "Validator.h"
#include <regex>
#include <iostream>

ValidationException::ValidationException(std::string& _message) : message(_message) {}

const char* ValidationException::what() const noexcept {
	return message.c_str();
}

bool Validator::validateString(std::string& input) {
	for (char i : input)
		if (isdigit(i) != false)
			return false;
	return true;
}

bool Validator::validCoatSize(int size)
{
	return size >= 0;
}

bool Validator::validCoatColour(std::string colour)
{
	std::string errors;
	if (!validateString(colour))
		errors += std::string("The colour contains digits.");
	if (!errors.empty())
		throw ValidationException(errors);
	return !colour.empty();
}

bool Validator::validCoatPrice(int price)
{
	return price >= 0;
}

bool Validator::validCoatQuantity(int quantity)
{
	return quantity >= 0;
}

bool Validator::validCoatPhotograph(std::string photograph)
{
	return std::regex_match(photograph, std::regex("(^https:\/\/)?([a-zA-Z])+\.([a-z]{2,})(\/(.)+)?"));
}
