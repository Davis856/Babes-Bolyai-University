#include "Star.h"

Star::Star(std::string name, std::string cons, int rightAsc, int dec, int diameter)
{
	this->name = name;
	this->cons = cons;
	this->rightAsc = rightAsc;
	this->dec = dec;
	this->diameter = diameter;
}

std::istream& operator>>(std::istream& input, Star& s)
{
	input >> s.name >> s.cons >> s.rightAsc >> s.dec >> s.diameter;
	return input;
}

std::ostream& operator<<(std::ostream& output, const Star& s)
{
	output << s.name << " " << s.cons << " " << s.rightAsc << " " << s.dec << " " << s.diameter;
	return output;
}