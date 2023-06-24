#include "Astronomer.h"

Astronomer::Astronomer(std::string name, std::string cons)
{
	this->name = name;
	this->cons = cons;
}

std::vector<std::string> Astronomer::tokenize(std::string str, char delimiter)
{
	std::vector<std::string> result;
	std::stringstream ss(str);
	std::string token;
	while (getline(ss, token, delimiter))
		result.push_back(token);

	return result;
}

std::istream& operator>>(std::istream& input, Astronomer& a)
{
	std::string line;
	getline(input, line);
	std::vector<std::string> tokens = Astronomer::tokenize(line, ',');
	if (tokens.size() != 2)
		return input;

	a.name = tokens[0];
	a.cons = tokens[1];

	return input;
}

std::ostream& operator<<(std::ostream& output, const Astronomer& a)
{
	output << a.name << "," << a.cons;
	return output;
}