#pragma once

#include <string>
#include <sstream>
#include <iostream>

class Star
{
private:
	std::string name;
	std::string cons;
	int rightAsc = 0;
	int dec = 0;
	int diameter = 0;

public:
	Star() {};
	Star(std::string name, std::string cons, int rightAsc, int dec, int diameter);
	~Star() {};

	inline std::string getName() { return this->name; }
	inline std::string getCons() { return this->cons; }

	inline int getRA() { return this->rightAsc; }
	inline int getDec() { return this->dec; }
	inline int getDiameter() { return this->diameter; }

	inline void setName(std::string newName) { this->name = newName; }
	inline void setRA(int newRa) { this->rightAsc = newRa; }
	inline void setDec(int newDec) { this->dec = newDec; }
	inline void setDiameter(int newDiameter) { this->diameter = newDiameter; }

	friend std::istream& operator>>(std::istream&, Star&);
	friend std::ostream& operator<<(std::ostream&, const Star&);
};