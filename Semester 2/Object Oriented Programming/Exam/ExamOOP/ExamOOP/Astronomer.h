#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <iostream>

class Astronomer
{
private:
	std::string name;
	std::string cons;

public:
	Astronomer() {};
	Astronomer(std::string name, std::string cons);
	~Astronomer() {};

	inline std::string getName() { return this->name; }
	inline std::string getCons() { return this->cons; }

	static std::vector<std::string> tokenize(std::string str, char delimiter);
	friend std::ostream& operator<<(std::ostream&, const Astronomer&);
	friend std::istream& operator>>(std::istream&, Astronomer&);

};

//For 2 QTableView
