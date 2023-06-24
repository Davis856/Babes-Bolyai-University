#include "RepoAstronomer.h"
#include <fstream>

RepoAstronomer::RepoAstronomer()
{
	this->LoadData();
}

std::vector<Astronomer>& RepoAstronomer::getAstronomers()
{
	return this->astronomers;
}

void RepoAstronomer::LoadData()
{
	std::ifstream inFile("astronomers.txt");
	Astronomer currentElement;
	this->astronomers.clear();
	while (inFile >> currentElement)
	{
		this->astronomers.push_back(currentElement);
	}
	inFile.close();
}