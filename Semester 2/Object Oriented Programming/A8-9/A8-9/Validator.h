#pragma once
#include "Coat.h"

class Validator
{
public:
	static bool validCoat(int size, std::string colour, int price, int quantity, std::string photograph);
	static bool validateString(std::string& input);
	static bool validCoatSize(int size);
	static bool validCoatColour(std::string colour);
	static bool validCoatPrice(int price);
	static bool validCoatQuantity(int quantity);
	static bool validCoatPhotograph(std::string photograph);
};

class ValidationException : public std::exception {
private:
	std::string message;
public:
	explicit ValidationException(std::string& _message);

	const char* what() const noexcept override;
};